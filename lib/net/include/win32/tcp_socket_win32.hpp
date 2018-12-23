#pragma once

#include <ws2tcpip.h>

namespace rvi
{
    class tcp_socket
    {
    public:
        SOCKET sock;
        sockaddr addr;

        tcp_socket(SOCKET sock, sockaddr addr);
        ~tcp_socket();
    };
}