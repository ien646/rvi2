#include "server.hpp"

#include <thread>
#include <functional>

#include "msg_builder.hpp"

namespace rvi
{
    server::server(uint16_t listen_port)
        : _listener(listen_port)
    { }

    void server::start()
    {
        _listener.enable_listen([&](tcp_connection conn)
        {
            this->connection_callback(conn);
        });
    }

    void server::connection_callback(tcp_connection conn)
    {
        int cid = _runtime.create_client();
        auto th = std::thread([&]()
        {
            _runtime.start_client(cid);
            connection_life(conn, cid);
        });
        th.detach();
    }

    void server::connection_life(tcp_connection conn, int cid)
    {
        connection_init(conn, cid);
        while(true)
        {

        }
    }

    void server::connection_init(tcp_connection conn, int cid)
    {
        // ...
    }
}