#pragma once

#include <unordered_map>
#include <client_context.hpp>

#include "host_types.hpp"

namespace rvi::host
{
    class std_bindings
    {
    public:
        static void print(cid_t, runtime&, const arglist_t&);
    };

    struct std_binding_entry
    {
        std::string name;
        runtime_inst_t call;

        std_binding_entry(const std::string& name, runtime_inst_t call)
        {
            this->name = name;
            this->call = call;
        }
    };

    static std::vector<std_binding_entry> std_bindings_list =
    {
        std_binding_entry("print", &std_bindings::print)
    };
}