#if defined(_WIN32)

#include <rvi/tcp_connection.hpp>

#include <array>

namespace rvi
{
    tcp_connection::tcp_connection(SOCKET sock)
        : _sock(sock)
    {    }

    void tcp_connection::close()
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
        return true;
    }

    bool tcp_connection::receive_data(std::vector<uint8_t>& result, size_t maxbuff = 4096)
    {
        result.resize(4096);
        int bytes_read = recv(_sock, reinterpret_cast<char*>(result.data()), maxbuff, NULL);
        if(bytes_read == 0 || bytes_read == SOCKET_ERROR)
        {
            return false;
        }
        result.resize(bytes_read);
        return true;
    }

    bool tcp_connection::send_data(const std::vector<char>& data)
    {
        int bytes_sent = send(_sock, data.data(), data.size(), NULL);
        return ((bytes_sent != 0) && (bytes_sent != SOCKET_ERROR));
    }

    bool tcp_connection::send_data(const std::vector<uint8_t>& data)
    {
        int bytes_sent = send(
            _sock, 
            reinterpret_cast<const char*>(data.data()), 
            data.size(), 
            NULL
        );
        return ((bytes_sent != 0) && (bytes_sent != SOCKET_ERROR));
    }

    void tcp_connection::operator=(const tcp_connection& cp_src)
    {
        _sock = cp_src._sock;
        _moved = cp_src._moved;
    }

    void tcp_connection::operator=(tcp_connection&& mv_src)
    {
        _sock = mv_src._sock;
        _moved = mv_src._moved;
        mv_src._moved = true;
    }
}

#endif