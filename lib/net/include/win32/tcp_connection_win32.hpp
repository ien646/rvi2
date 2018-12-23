#pragma once

#include <cinttypes>
#include <vector>

#include "win32/tcp_common_win32.hpp"

namespace rvi
{
    class tcp_connection
    {
    private:
        SOCKET _sock;

    public:
        tcp_connection(SOCKET sock);
        ~tcp_connection();

        bool receive_data(std::vector<char>& result, size_t maxbuff);
        bool send_data(const std::vector<char>& data);
    };
}