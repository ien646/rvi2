#pragma once

#include <unordered_map>
#include <cinttypes>
#include <client_context.hpp>
#include <serializer.hpp>

namespace rvi::host
{
    typedef int client_id;
    typedef std::vector<std::vector<std::uint8_t>> cmdlist_t;
    class runtime
    {
    private:
        std::unordered_map<client_id, client_context> _clients;
        client_id _last_cid = 0;
        
    public:
        runtime() { }
        client_id create_client();
        void start_client(client_id cid, std::stringstream& program);
        cmdlist_t get_update_commands(client_id cid);
    };
}