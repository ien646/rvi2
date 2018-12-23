#include "win32/tcp_connection_win32.hpp"

#include <array>

namespace rvi
{
    tcp_connection::~tcp_connection()
    {
        closesocket(_sock);
    }

    bool tcp_connection::receive_data(std::vector<char>& result, size_t maxbuff = 4096)
    {
        result.resize(4096);
        int bytes_read = recv(_sock, result.data(), maxbuff, NULL);
        if(bytes_read == 0 || bytes_read == SOCKET_ERROR)
        {
            return false;
        }
        result.resize(bytes_read);
    }

    bool tcp_connection::send_data(const std::vector<char>& data)
    {
        int bytes_sent = send(_sock, data.data(), data.size(), NULL);
        return ((bytes_sent != 0) && (bytes_sent != SOCKET_ERROR));
    }
}