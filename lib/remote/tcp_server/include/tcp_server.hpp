#pragma once

#include <runtime.hpp>
#include <tcp_listener.hpp>
#include <tcp_connection.hpp>

namespace rvi
{
    class tcp_server
    {
    private:
        tcp_listener _listener;
        runtime _runtime;

    public:
        tcp_server(uint16_t listen_port);
        void start();

    private:
        void connection_callback(tcp_connection conn);
        void connection_life(tcp_connection conn, int cid);
        void connection_init(tcp_connection conn, int cid);
    };
}