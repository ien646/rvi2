#include "win32/tcp_client_win32.hpp"

#include <iostream>

#include "win32/tcp_common_win32.hpp"

namespace rvi
{
    tcp_client::tcp_client(const std::string& host_addr, uint16_t port)
    {
        if (!init_wsa(&_wsadata))
        {
            return;
        }
        _wsa_initialized = true;
        fill_addrinfo(port, host_addr.c_str(), _addr_info);
    }

    tcp_client::~tcp_client()
    {
        if(_wsa_initialized)
        {
            WSACleanup();
        }
    }

    bool tcp_client::init_client_socket()
    {
        return create_socket(_addr_info, &_client_sock);
    }

    bool tcp_client::connect_client_socket()
    {
        int result = connect(
            _client_sock, 
            _addr_info->ai_addr, 
            static_cast<int>(_addr_info->ai_addrlen)
        );

        if (result == SOCKET_ERROR) {
            closesocket(_client_sock);
            _client_sock = INVALID_SOCKET;
            return false;
        }
        return true;
    }

    bool tcp_client::enable_connect(connection_callback_t cback)
    {
        if(!init_client_socket())
        {
            return false;
        }

        if(!connect_client_socket())
        {
            return false;
        }

        cback(tcp_connection(_client_sock));
        return true;
    }
}