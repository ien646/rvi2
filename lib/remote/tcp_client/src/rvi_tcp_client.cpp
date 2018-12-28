#include "rvi_tcp_client.hpp"

namespace rvi
{
    rvi_tcp_client::rvi_tcp_client(const std::string& host, uint16_t port)
        : _client(host, port)
        , _connection(NULL)
    { }

    void rvi_tcp_client::connect()
    {
        _client.enable_connect([&](tcp_connection conn)
        {
            _connection = std::move(conn);
            init_lifetime();
        });
    }

    void rvi_tcp_client::setup_msg_callback(msg_callback_t cback)
    {
        _msg_cback = cback;
    }

    void rvi_tcp_client::init_lifetime()
    {
        message_data_t msg;
        while(_connection.receive_data(msg, 4096))
        {
            _msg_cback(_connection, std::move(msg));
        }
    }

    void rvi_tcp_client::user_click(vector2 pos)
    {
        message_data_t msg = msg_builder::msg_user_click(pos);
        _connection.send_data(msg);
    }

    void rvi_tcp_client::user_key(char key)
    {
        message_data_t msg = msg_builder::msg_user_key(key);
        _connection.send_data(msg);
    }

    void rvi_tcp_client::request_snapshot()
    {
        _connection.send_data(msg_builder::msg_request_snapshot());
    }
}