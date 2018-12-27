#include "tcp_server.hpp"

#include <thread>
#include <functional>

#include "msg_builder.hpp"
#include "msg_header.hpp"

namespace rvi
{
    tcp_server::tcp_server(uint16_t listen_port)
        : _listener(listen_port)
    { }

    void tcp_server::start()
    {
        _listener.enable_listen([&](tcp_connection conn)
        {
            this->connection_callback(conn);
        });
    }

    void tcp_server::connection_callback(tcp_connection conn)
    {
        int cid = _runtime.create_client();
        auto th = std::thread([&]()
        {
            _runtime.start_client(cid);
            connection_life(conn, cid);
        });
        th.detach();
    }

    void tcp_server::connection_life(tcp_connection conn, int cid)
    {
        connection_init(conn, cid);
        message_data_t msg;
        while(conn.receive_data(msg, 4096))
        {
            switch(static_cast<msg_header>(msg[0]))
            {
                case msg_header::USER_CLICK:
                    process_user_click_msg(msg, conn, cid);
                    break;
                case msg_header::USER_KEY:
                    process_user_key_msg(msg, conn, cid);
                    break;
                case msg_header::REQUEST_SNAPSHOT:
                    send_snapshot(conn, cid);
                    break;
            }
        }
    }

    void tcp_server::process_user_click_msg(message_data_t msg, tcp_connection conn, int cid)
    {
        // ...
    }

    void tcp_server::process_user_key_msg(message_data_t msg, tcp_connection conn, int cid)
    {
        // ...
    }

    void pack_msg_data(message_data_t& dst, message_data_t&& src)
    {
        dst.reserve(dst.size() + src.size());
        std::move(src.begin(), src.end(), std::back_inserter(dst));
    }

    void tcp_server::connection_init(tcp_connection conn, int cid)
    {
        send_snapshot(conn, cid);
    }

    void tcp_server::send_snapshot(tcp_connection conn, int cid)
    {
        auto snapshot = _runtime.snapshot_diff_relative(cid);

        conn.send_data(msg_builder::msg_begin_seq());

        message_data_t packed_msg;

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