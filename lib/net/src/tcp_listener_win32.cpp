#include "tcp_listener_win32.hpp"

#include <thread>

client_socket::client_socket(SOCKET sock, sockaddr addr)
    : sock(sock)
    , addr(addr)
{ }

client_socket::~client_socket()
{
    closesocket(sock);
}

tcp_listener::tcp_listener(uint16_t port)
{
    if (!init_wsa())
    {
        return;
    }
    fill_addrinfo(port);
}

void tcp_listener::enable_listen(accept_callback_t cback)
{
    if (!init_listen_socket())
    {
        return;
    }
    if(!start_listen())
    {
        return;
    }
    std::thread th(&tcp_listener::start_accept, this, cback);
    th.join();
}

bool tcp_listener::init_wsa()
{
    int err = WSAStartup(MAKEWORD(2, 2), &_wsadata);
    if (err != 0)
    {
        std::cout << "Error during WSA initialization! ERR_N:"
            << err
            << std::endl;
        return false;
    }
    return true;
}

addrinfo tcp_listener::get_socket_hints()
{
    addrinfo result;
    ZeroMemory(&result, sizeof(decltype(result)));
    result.ai_family = AF_INET;
    result.ai_socktype = SOCK_STREAM;
    result.ai_protocol = IPPROTO_TCP;
    result.ai_flags = AI_PASSIVE;
    return result;
}

bool tcp_listener::fill_addrinfo(uint16_t port)
{
    addrinfo sock_hints = get_socket_hints();
    int res = getaddrinfo(
        NULL,
        std::to_string(port).c_str(),
        &sock_hints,
        &_addr_info);

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

bool tcp_listener::init_listen_socket()
{
    if (!create_socket())
    {
        return false;
    }
    if (!bind_socket())
    {
        return false;
    }
    return true;
}

bool tcp_listener::create_socket()
{
    _listen_sock = socket(
        _addr_info->ai_family, 
        _addr_info->ai_socktype, 
        _addr_info->ai_protocol
    );
    
    if (_listen_sock == INVALID_SOCKET)
    {
        std::cout << "Error during socket initialization! ERR_N: "
            << WSAGetLastError()
            << std::endl;
        freeaddrinfo(_addr_info);
        WSACleanup();
        return false;
    }
    return true;
}

bool tcp_listener::bind_socket()
{
    int res = bind(
        _listen_sock,
        _addr_info->ai_addr,
        static_cast<int>(_addr_info->ai_addrlen)
    );

    if (res != 0)
    {
        std::cout << "Error binding socket! ERR_N: " << res << std::endl;
        freeaddrinfo(_addr_info);
        closesocket(_listen_sock);
        WSACleanup();
        return false;
    }
    return true;
}

bool tcp_listener::start_listen()
{
    int result = listen(_listen_sock, SOMAXCONN);
    if(result != 0)
    {
        std::cout << "Error listening on socket! ERR_N: " << result << std::endl;
        return false;
    }
    std::cout << "Socket started listening succesfully!" << std::endl;
    return true;
}

void tcp_listener::start_accept(accept_callback_t cback)
{
    using namespace std::chrono_literals;
    for(;;)
    {
        ioctlsocket(_listen_sock, FIONBIO, 0);
        sockaddr client_addrinfo;
        int sz = sizeof(client_addrinfo);

        std::cout << "Awaiting for new client connection..." << std::endl;
        SOCKET csck = accept(_listen_sock, &client_addrinfo, &sz);
        if(csck == INVALID_SOCKET)
        {
            std::cout << "Accepted invalid socket! Skipping..." << std::endl;
        }
        cback(client_socket(csck, client_addrinfo));
    }
}