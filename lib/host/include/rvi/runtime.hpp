#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <cinttypes>

#include <rvi/client_instance.hpp>

namespace rvi
{
    typedef std::function<void(client_instance&, frame*)> binding_t;
    typedef uint64_t rvi_cid_t;

    class runtime
    {
    private:
        uint64_t _cid_accum = 0ul; // client-id accumulator
        std::unordered_map<rvi_cid_t ,std::unique_ptr<client_instance>> _client_instances;
        std::unordered_map<std::string, binding_t> _bindings;

    public:
        rvi_cid_t create_client();
        void start_client(rvi_cid_t cid);

        client_instance& get_instance(rvi_cid_t);

        void create_binding(const std::string& bname, binding_t bcall);
        void delete_binding(const std::string& bname);
        void exec_binding(client_instance& cinst, const std::string& bname, frame* fptr);

        line_container snapshot_full_flat(rvi_cid_t) const;
        relative_snapshot snapshot_full_relative(rvi_cid_t);
        relative_snapshot snapshot_diff_relative(rvi_cid_t);
    };
} 
