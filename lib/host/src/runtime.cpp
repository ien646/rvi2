#include "runtime.hpp"

namespace rvi::host
{
    client_id runtime::create_client()
    {
        client_id cid = _last_cid++;
        client_context cctx;

        _clients.emplace(cid, std::move(cctx));
        return cid;
    }

    void runtime::start_client(client_id cid)
    {
        //...
    }
}