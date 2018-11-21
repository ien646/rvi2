#include "runtime.hpp"

namespace rvi
{
    client_instance& runtime::get_instance(int inst_id)
    {
        if(_client_instances.count(inst_id) == 0)
        {
            throw std::invalid_argument("Invalid client instance id:" + std::to_string(inst_id));
        }
        return _client_instances.at(inst_id);
    }

    const std::string& runtime::get_include_path(const std::string& name)
    {
        return _include_filepaths[name];
    }

    bool runtime::is_include_cached(const std::string& name)
    {
        return (_include_cache.count(name) > 0);
    }

    const std::vector<parsed_stmt>& runtime::get_cached_include(const std::string& name)
    {
        return _include_cache.at(name);
    }

    void runtime::cache_parsed_include(const std::string& name, std::vector<parsed_stmt> instructions)
    {
        _include_cache[name] = instructions;
    }
}