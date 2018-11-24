#include "client_instance.hpp"

#include <iostream>

#include "call_map.hpp"

namespace rvi
{
    client_instance::client_instance(runtime* rptr)
        : _runtime_ptr(rptr)
    { }

    void client_instance::push_include(const std::string& inc_file)
    {
        data.include_stack.push_back(inc_file);
    }

    const std::string& client_instance::peek_current_include() const
    {
        return data.include_stack.back();
    }

    void client_instance::pop_include()
    {
        data.include_stack.pop_back();
    }

    void client_instance::mark_include_once()
    {
        data.include_once_ids.emplace(peek_current_include());
    }

    runtime* client_instance::runtime_ptr()
    {
        return _runtime_ptr;
    }

    void client_instance::exec_definition(const std::string& dname)
    {
        if(data.definitions.count(dname) > 0)
        {
            auto def = data.definitions.at(dname);
            for(auto& inst : def)
            {
                auto& call = call_map.at(inst.cmd);
                call(*this, inst.args);
            }
        }
        else
        {
            std::cerr   << "Attempt to use undefined definition ["
                        << dname
                        << "]"
                        << std::endl;
        }
    }
}