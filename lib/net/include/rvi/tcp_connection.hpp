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
        bool _moved = false;

    public:
        tcp_connection() = delete;
        tcp_connection(SOCKET sock);
        tcp_connection(const tcp_connection& cp_src) = default;
        tcp_connection(tcp_connection&& mv_src) = default;
        
        void close();

        bool receive_data(std::vector<char>& result, size_t maxbuff);
        bool receive_data(std::vector<uint8_t>& result, size_t maxbuff);
        bool send_data(const std::vector<char>& data);
        bool send_data(const std::vector<uint8_t>& data);

        void operator=(const tcp_connection& cp_src);
        void operator=(tcp_connection&& mv_src);
    };
    
    typedef std::function<void(tcp_connection)> connection_callback_t;
}

// ################## POSIX ##################
#elif defined(_POSIX_VERSION)
// ...
#endif