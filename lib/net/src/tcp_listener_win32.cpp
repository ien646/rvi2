#include "tcp_listener.hpp"

#include <thread>
#include <string>

#include "tcp_common.hpp"

namespace rvi
{   
    tcp_listener::tcp_listener(uint16_t port)
    {
        if (!init_wsa(&_wsadata))
        {
            return;
        }
        _wsa_initialized = true;
        fill_addrinfo(port, "", _addr_info, true);
    }

    tcp_listener::~tcp_listener()
    {
        if(_wsa_initialized)
        {
            WSACleanup();
        }
    }

    void tcp_listener::enable_listen(connection_callback_t cback)
    {
        if (!init_listen_socket())
        {
            return;
        }
        if(!start_listen())
        {
            return;
        }
        std::thread th(&tcp_listener::start_accept, this, cback);
        th.join();
    }

    bool tcp_listener::init_listen_socket()
    {
        if (!create_socket(_addr_info, &_listen_sock))
        {
            return false;
        }
        if (!bind_socket(_listen_sock, _addr_info))
        {
            return false;
        }
        return true;
    }

    bool tcp_listener::start_listen()
    {
        int result = listen(_listen_sock, SOMAXCONN);
        if(result != 0)
        {
            std::cout << "Error listening on socket! ERR_N: " << result << std::endl;
            return false;
        }
        std::cout << "Socket started listening succesfully!" << std::endl;
        return true;
    }

    void tcp_listener::start_accept(connection_callback_t cback)
    {
        using namespace std::chrono_literals;
        for(;;)
        {
            ioctlsocket(_listen_sock, FIONBIO, 0);
            sockaddr client_addrinfo;
            int sz = sizeof(client_addrinfo);

            std::cout << "Awaiting for new client connection..." << std::endl;
            SOCKET csck = accept(_listen_sock, &client_addrinfo, &sz);
            if(csck == INVALID_SOCKET)
            {
                std::cout << "Accepted invalid socket! Skipping..." << std::endl;
            }
            auto th = std::thread([&]()
            {
                cback(tcp_connection(csck));
            });
            th.join();
        }
    }
}