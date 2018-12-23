#include "win32/tcp_socket_win32.hpp"

namespace rvi
{
    tcp_socket::tcp_socket(SOCKET sock, sockaddr addr)
        : sock(sock)
        , addr(addr)
    { }

    tcp_socket::~tcp_socket()
    {
        closesocket(sock);
    }
}