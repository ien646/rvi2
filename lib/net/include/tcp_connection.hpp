#pragma once

// ################## WIN32 ##################
#if defined(_WIN32)

#include <cinttypes>
#include <vector>
#include <functional>

#include "tcp_common.hpp"

namespace rvi
{
    class tcp_connection
    {
    private:
        SOCKET _sock;

    public:
        tcp_connection() = delete;
        tcp_connection(SOCKET sock);
        tcp_connection(const tcp_connection& cp_src) = delete;
        tcp_connection(tcp_connection&& mv_src) = default;
        
        void close();

        bool receive_data(std::vector<char>& result, size_t maxbuff);
        bool send_data(const std::vector<char>& data);
    };
    
    typedef std::function<void(tcp_connection)> connection_callback_t;
}

// ################## POSIX ##################
#elif defined(_POSIX_VERSION)
// ...
#endif