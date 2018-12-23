#include "win32/tcp_common_win32.hpp"

#include <iostream>

namespace rvi
{
    addrinfo get_socket_hints(bool will_bind)
    {
        addrinfo result;
        ZeroMemory(&result, sizeof(decltype(result)));
        result.ai_family = AF_INET;
        result.ai_socktype = SOCK_STREAM;
        result.ai_protocol = IPPROTO_TCP;
        result.ai_flags = will_bind ? AI_PASSIVE : NULL;
        return result;
    }

    bool init_wsa(WSADATA* wsadata)
    {
        int err = WSAStartup(MAKEWORD(2, 2), wsadata);
        if (err != 0)
        {
            std::cout << "Error during WSA initialization! ERR_N:"
                << err
                << std::endl;
            return false;
        }
        return true;
    }

    bool fill_addrinfo(uint16_t port, const std::string host_addr, addrinfo* result)
    {
        addrinfo sock_hints = get_socket_hints();
        int res = getaddrinfo(
            host_addr.empty() ? NULL : host_addr.c_str(),
            std::to_string(port).c_str(),
            &sock_hints,
            &result);

        if (res != 0)
        {
            std::cout << "Unable to get address info for port: "
                << port
                << "; ERR_N: "
                << res
                << std::endl;
            WSACleanup();
            return false;
        }
        return true;
    }

    bool create_socket(addrinfo* ainfo, SOCKET* result)
    {
        *result = socket(
            ainfo->ai_family, 
            ainfo->ai_socktype, 
            ainfo->ai_protocol
        );
        
        if (*result == INVALID_SOCKET)
        {
            std::cout << "Error during socket initialization! ERR_N: "
                << WSAGetLastError()
                << std::endl;
            freeaddrinfo(ainfo);
            WSACleanup();
            return false;
        }
        return true;
    }

    bool bind_socket(SOCKET sock, addrinfo* ainfo)
    {
        int res = bind(
            sock,
            ainfo->ai_addr,
            static_cast<int>(ainfo->ai_addrlen)
        );

        if (res != 0)
        {
            std::cout << "Error binding socket! ERR_N: " << res << std::endl;
            freeaddrinfo(ainfo);
            closesocket(sock);
            WSACleanup();
            return false;
        }
        return true;
    }
}