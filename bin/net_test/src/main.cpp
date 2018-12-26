#include <thread>
#include <functional>
#include <iostream>

#include "tcp_listener.hpp"
#include "tcp_connection.hpp"

using namespace rvi;

int main()
{
    tcp_listener listener(8512);

    std::cout << "# LISTENING..." << std::endl;

    int ccount = 0;

    listener.enable_listen([&ccount](tcp_connection conn)
    {
        std::cout << "Accepted client no. [" << ccount << "]" << std::endl;
        std::vector<char> data;
        char value = 0;
        while(true)
        {
            data.clear();
            data.push_back(value);
            conn.send_data(data);
            
            if(!conn.receive_data(data, 512))
            {
                std::cout << "Disconnected client no. [" << ccount << "]" << std::endl;
                break;
            }
        }
    });
}