#pragma once

#include <unordered_map>
#include <client_context.hpp>

namespace rvi::host
{
    typedef std::function<void(client_context&, const std::vector<std::string>&)> std_binding_call_t;

    class std_bindings
    {
    public:
        static void print(client_context& ctx, const std::vector<std::string>& args);
    };

    struct std_binding_entry
    {
        std::string name;
        std_binding_call_t call;

        std_binding_entry(const std::string& name, std_binding_call_t call)
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