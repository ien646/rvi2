#pragma once

#include <string>
#include <cinttypes>

#include "msg_builder.hpp"
#include "tcp_client.hpp"

namespace rvi
{
    typedef std::function<void(tcp_connection, message_data_t&&)> msg_callback_t;
    class rvi_tcp_client
    {
    private:
        tcp_client _client;
        tcp_connection _connection;
        msg_callback_t _msg_cback;

    public:
        rvi_tcp_client(const std::string& host, uint16_t port);
        void setup_msg_callback(msg_callback_t);
        void connect();

        void user_click(vector2 pos);
        void user_key(char key);
        void request_snapshot();

    private:
        void init_lifetime();
    };
}