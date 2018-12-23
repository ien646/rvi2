#pragma once

#if !defined(_WIN32)
#error "Unable to use Windows tcp sockets on non Windows compatible platform"
#endif

#include <ws2tcpip.h>
#include <cinttypes>
#include <string>
#include <functional>

#include "win32/tcp_connection_win32.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace rvi
{
    typedef std::function<void(tcp_connection)> connection_callback_t;

    addrinfo get_socket_hints(bool will_bind);

    bool init_wsa(WSADATA* wsadata);

    bool fill_addrinfo(uint16_t port, const std::string host_addr, addrinfo* result, bool will_bind);

    bool create_socket(addrinfo* ainfo, SOCKET* result);

    bool bind_socket(SOCKET sock, addrinfo* ainfo);
}