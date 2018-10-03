#pragma once

#include <unordered_map>
#include <client_context.hpp>

namespace rvi::host
{
    typedef int client_id;

    class runtime
    {
    private:
        std::unordered_map<client_id, client_context> _clients;
        client_id _last_cid = 0;
        
    public:
        runtime() { }
        client_id create_client();
        void start_client(client_id cid, std::stringstream& program);
    };
}