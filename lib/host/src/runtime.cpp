#include <rvi/runtime.hpp>

namespace rvi
{
    rvi_cid_t runtime::create_client()
    {
        rvi_cid_t cid = _cid_accum++;
        _client_instances.emplace(cid, std::make_unique<client_instance>(this));
        return cid;
    }

    void runtime::start_client(rvi_cid_t cid)
    {
        return; // ...
    }

    client_instance& runtime::get_instance(rvi_cid_t cid)
    {
        return *_client_instances.at(cid);
    }

    void runtime::create_binding(const std::string& bname, binding_t bcall)
    {
        if(_bindings.count(bname) > 0)
        {
            _bindings.erase(bname);
        }
        _bindings.emplace(bname, bcall);
    }

    void runtime::delete_binding(const std::string& bname)
    {
        _bindings.erase(bname);
    }

    void runtime::exec_binding(client_instance& cinst, const std::string& bname, frame* fptr)
    {
        if(_bindings.count(bname) > 0)
        {
            binding_t& bnd = _bindings.at(bname);
            bnd(cinst, fptr);
        }
    }

    std::vector<line> runtime::snapshot_full_flat(rvi_cid_t cid) const
    {
        return _client_instances.at(cid)->snapshot_full_flat();
    }

    relative_snapshot runtime::snapshot_full_relative(rvi_cid_t cid)
    {
        return _client_instances.at(cid)->snapshot_full_relative();
    }

    relative_snapshot runtime::snapshot_diff_relative(rvi_cid_t cid)
    {
        return _client_instances.at(cid)->snapshot_diff_relative();
    }
}