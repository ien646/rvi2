#pragma once

// ################## WIN32 ##################
#if defined(_WIN32)

#include <ws2tcpip.h>
#include <cinttypes>
#include <string>

#include "tcp_connection.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

namespace rvi
{
    addrinfo get_socket_hints(bool will_bind);

    bool init_wsa(WSADATA* wsadata);

    bool fill_addrinfo(uint16_t port, const std::string host_addr, PADDRINFOA& result, bool will_bind);

    bool create_socket(PADDRINFOA ainfo, SOCKET* result);

    bool bind_socket(SOCKET sock, PADDRINFOA ainfo);
}

// ################## POSIX ##################
#elif defined(_POSIX_VERSION)
// ...
#endif