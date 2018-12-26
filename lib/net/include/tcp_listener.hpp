#pragma once

#if defined(_WIN32)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>

#include <functional>

#include "tcp_common.hpp"
#include "tcp_connection.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace rvi
{
    class tcp_listener
    {
    private:
        bool _wsa_initialized = false;
        WSADATA _wsadata;
        addrinfo* _addr_info;
        SOCKET _listen_sock;

    public: 
        tcp_listener(uint16_t port);
        ~tcp_listener();
        void enable_listen(connection_callback_t cback);

    private:
        bool init_listen_socket();
        bool start_listen();
        void start_accept(connection_callback_t cback);
    };
}

#elif defined(_POSIX_VERSION)
// ...
#endif