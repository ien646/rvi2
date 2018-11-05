#include "tcp_listener.hpp"

#include <iostream>
#include <thread>
#include <iostream>
#include <array>

static void accept_callback(client_socket sock)
{
    SOCKET socket = sock.sock;
    std::cout << "Accepted new socket!" << std::endl;
    std::array<char, 512> buff;
    memset(buff.data(), 0x00, buff.size());
    
    int recv_res = recv(socket, buff.data(), static_cast<int>(buff.size()), NULL);
    if(recv_res < 0)
    {
        std::cout << "Error during recv(*)! ERR_N: " << WSAGetLastError() << std::endl;
        return;
    }
    
    int send_res = send(socket, buff.data(), static_cast<int>(buff.size()), NULL);
    if(send_res < 0)
    {
        std::cout << "Error during send(*)! ERR_N: " << WSAGetLastError() << std::endl;    
        return;    
    }
}

int main()
{
    tcp_listener listener(5555);
    listener.enable_listen(accept_callback);
}