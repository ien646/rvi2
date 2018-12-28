#include "rvi_tcp_server.hpp"

#include <thread>
#include <functional>

#include <serialization.hpp>
#include "msg_builder.hpp"
#include "msg_header.hpp"

namespace rvi
{
    rvi_tcp_server::rvi_tcp_server(uint16_t listen_port)
        : _listener(listen_port)
    { }

    void rvi_tcp_server::start()
    {
        _listener.enable_listen([&](tcp_connection conn)
        {
            this->connection_callback(conn);
        });
    }

    void rvi_tcp_server::connection_callback(tcp_connection conn)
    {
        int cid = _runtime.create_client();
        auto th = std::thread([&]()
        {
            _runtime.start_client(cid);
            connection_life(conn, cid);
        });
        th.detach();
    }

    void rvi_tcp_server::connection_life(tcp_connection conn, int cid)
    {
        connection_init(conn, cid);
        message_data_t msg;
        while(conn.receive_data(msg, 4096))
        {
            switch(static_cast<msg_header>(msg[0]))
            {
                case msg_header::USER_CLICK:
                    process_user_click_msg(msg, conn, cid);
                    send_snapshot(conn, cid);
                    break;
                case msg_header::USER_KEY:
                    process_user_key_msg(msg, conn, cid);
                    send_snapshot(conn, cid);
                    break;
                case msg_header::REQUEST_SNAPSHOT:
                    send_snapshot(conn, cid);
                    break;
                default:
                    break;
            }
        }
    }

    void rvi_tcp_server::process_user_click_msg(message_data_t msg, tcp_connection conn, int cid)
    {
        rvi_assert(msg.size() == 9, "Invalid message data!");
        vector2 pos = deserialize_vector2(msg, 1);
        _runtime.get_instance(cid).user_click(pos);
    }

    void rvi_tcp_server::process_user_key_msg(message_data_t msg, tcp_connection conn, int cid)
    {
        rvi_assert(msg.size() == 2, "Invalid message data!");
        char ch = deserialize_integral<char>(msg, 1);
        _runtime.get_instance(cid).key_press(ch);
    }

    void pack_msg_data(message_data_t& dst, message_data_t&& src)
    {
        dst.reserve(dst.size() + src.size());
        std::move(src.begin(), src.end(), std::back_inserter(dst));
    }

    void rvi_tcp_server::connection_init(tcp_connection conn, int cid)
    {
        send_snapshot(conn, cid);
    }

    void rvi_tcp_server::send_snapshot(tcp_connection conn, int cid)
    {
        auto snapshot = _runtime.snapshot_diff_relative(cid);
        if(snapshot.empty())
        {
            conn.send_data(msg_builder::msg_end_seq());
            return;
        }

        message_data_t packed_msg;
        conn.send_data(msg_builder::msg_begin_seq());
        for(auto& entry : snapshot)
        {
            if(entry.deleted)
            {
                pack_msg_data(packed_msg, msg_builder::msg_delete_frame(entry.name));
            }
            else
            {
                pack_msg_data(packed_msg, msg_builder::msg_select_frame(entry.name));
                pack_msg_data(packed_msg, msg_builder::msg_draw_lines(entry.lines));
            }
        }
        pack_msg_data(packed_msg, msg_builder::msg_end_seq());
        conn.send_data(packed_msg);
    }
}