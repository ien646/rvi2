#pragma once

#include <stack>
#include <unordered_map>
#include <cinttypes>
#include <client_context.hpp>

namespace rvi::host
{
    typedef int cid_t;
    typedef std::vector<std::string> arglist_t;
    typedef std::vector<std::vector<std::uint8_t>> cmdlist_t;
    typedef std::function<void(client_context& ctx, const arglist_t& args)> binding_t;

    struct runtime_instance_data
    {
        std::unordered_map<std::string, binding_t> bindings;
        std::stack<std::string> include_stack;
        std::unordered_set<std::string> include_once_files;
    };

    class runtime
    {
    private:
        std::unordered_map<cid_t, client_context> _clients;  
        std::unordered_map<cid_t, runtime_instance_data> _client_rt_data;        
        cid_t _last_cid = 0;
        
    public:
        runtime() { }

        cid_t create_client();
        void start_client(cid_t cid, std::stringstream& program);

        void create_binding(cid_t cid, const std::string& name, binding_t call);
        void exec_binding(cid_t cid, const std::string& name, const arglist_t& args);      

        cmdlist_t get_update_commands(cid_t cid);
        std::vector<line> get_flat_snapshot(cid_t cid);

        void mark_include_once(cid_t cid);

        bool can_include(cid_t cid, const std::string fname);

        void push_include(cid_t cid, const std::string& fname);
        const std::string& current_include(cid_t cid);
        void pop_include(cid_t cid);

        void init_std_bindings(cid_t cid);      

        client_context* get_client(cid_t);  
    };
}