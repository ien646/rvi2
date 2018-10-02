#include "runtime.hpp"

#include "interpreter.hpp"

namespace rvi::host
{
    client_id runtime::create_client()
    {
        client_id cid = _last_cid++;
        client_context cctx;

        _clients.emplace(cid, std::move(cctx));
        return cid;
    }

    void runtime::start_client(client_id cid, std::stringstream& program)
    {
        client_context& ctx = _clients.at(cid);
        auto stmt_col = interpreter::read(program);
        interpreter::run(stmt_col, ctx);
    }
}