#pragma once

#if !defined(_WIN32)
#error "Unable to use Windows tcp sockets on non Windows compatible platform"
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <functional>

#include "win32/tcp_connection_win32.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace rvi
{
    class tcp_client
    {
    private:
        bool _wsa_initialized = false;
        WSADATA _wsadata;
        addrinfo* _addr_info;
        SOCKET _client_sock;

    public:
        tcp_client(const std::string& host_addr, uint16_t port);
        ~tcp_client();
        bool enable_connect(connection_callback_t cback);

    private:
        bool init_client_socket();
        bool connect_client_socket();
    };
}