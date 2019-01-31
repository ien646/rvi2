#include <rvi/runtime.hpp>

namespace rvi
{
    rvi_cid_t runtime::create_client()
    {
        rvi_cid_t cid = _cid_accum++;
        _client_instances.emplace(cid, client_instance(this));
        return cid;
    }

    void runtime::start_client(rvi_cid_t cid)
    {
        return; // ...
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
}