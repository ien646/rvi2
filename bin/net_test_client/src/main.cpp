#include <thread>
#include <functional>
#include <iostream>

#include "tcp_client.hpp"
#include "tcp_connection.hpp"

using namespace rvi;

int main()
{
    while(true)
    {
        tcp_client client("127.0.0.1", 8512);

        std::cout << "# AWAITING SERVER CONNECTION..." << std::endl;

        int ccount = 0;

        client.enable_connect([&ccount](tcp_connection conn)
        {
            std::cout << "Connected to server" << std::endl;
            std::vector<char> data;
            while(true)
            {
                if(!conn.receive_data(data, 512))
                {
                    std::cout << "Disconnected from server" << std::endl;
                    break;
                }
                std::cout << "Received data: " << data[0] << std::endl;
                data[0]++;

                using namespace std::chrono_literals;
                std::this_thread::sleep_for(100ms);

                if(!conn.send_data(data))
                {
                    std::cout << "Disconnected from server" << std::endl;
                    break;
                }
            }
            conn.close();
        });
    }
}

