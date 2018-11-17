#pragma once

#include <unordered_map>
#include <string>

#include "client_instance.hpp"

namespace rvi
{
    class runtime
    {
    private:
        std::unordered_map<int, client_instance> _client_instances;
        
    public:
        client_context& get_instance_client_ctx(int inst_id)
        {
            if(_client_instances.count(inst_id) == 0)
            {
                throw std::invalid_argument("Invalid client instance id:" + std::to_string(inst_id));
            }
            client_instance& inst = _client_instances[inst_id];
            return inst.context;
        }
    };
}