#pragma once

#include <unordered_map>
#include <cinttypes>
#include <client_context.hpp>


namespace rvi::host
{
    typedef int cid_t;
    typedef std::vector<std::vector<std::uint8_t>> cmdlist_t;
    typedef std::function<void(client_context& ctx)> binding_t;

    class runtime
    {
    private:
        std::unordered_map<cid_t, client_context> _clients;
        std::unordered_map<std::string, binding_t> _bindings;
        cid_t _last_cid = 0;
        
    public:
        runtime() { }

        cid_t create_client();
        void start_client(cid_t cid, std::stringstream& program);

        void create_binding(const std::string& name, binding_t call);
        void exec_binding(const std::string& name, client_context& ctx);
        
        cmdlist_t get_update_commands(cid_t cid);
        relative_snapshot_t get_diff_snapshot(cid_t cid);
    };
}