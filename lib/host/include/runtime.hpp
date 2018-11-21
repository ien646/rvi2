#pragma once

#include <unordered_map>
#include <string>

#include "client_instance.hpp"
#include "parsed_stmt.hpp"

namespace rvi
{
    class runtime
    {
    private:
        std::unordered_map<int, client_instance> _client_instances;
        std::unordered_map<std::string, std::string> _include_filepaths;
        std::unordered_map<std::string, std::vector<parsed_stmt>> _include_cache;
        
    public:
        client_instance& get_instance(
            int inst_id);
        
        const std::string& get_include_path(
            const std::string& name);
        
        bool is_include_cached(
            const std::string& name);
        
        const std::vector<parsed_stmt>& get_cached_include(
            const std::string& name);
        
        void cache_parsed_include(
            const std::string& name, 
            std::vector<parsed_stmt> instructions);
    };
}