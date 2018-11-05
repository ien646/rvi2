#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include <iostream>
#include <string>

#include <functional>

#pragma comment (lib, "Ws2_32.lib")

class client_socket
{
public:
    SOCKET sock;
    sockaddr addr;

    client_socket(SOCKET sock, sockaddr addr);
    ~client_socket();
};

typedef std::function<void(client_socket)> accept_callback_t;

class tcp_listener
{
private:
    WSADATA _wsadata;
    addrinfo* _addr_info;
    SOCKET _listen_sock;

public: 
    tcp_listener(uint16_t port);
    void enable_listen(accept_callback_t cback);

private:
    bool init_wsa();
    addrinfo get_socket_hints();
    bool fill_addrinfo(uint16_t port);
    bool init_listen_socket();
    bool create_socket();
    bool bind_socket();
    
    bool start_listen();
    void start_accept(accept_callback_t cback);
};