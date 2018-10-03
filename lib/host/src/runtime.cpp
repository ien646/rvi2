#include "runtime.hpp"

#include "interpreter.hpp"

namespace rvi::host
{
    client_id runtime::create_client()
    {
        _clients.emplace(++_last_cid, client_context{});
        return _last_cid;
    }

    void runtime::start_client(client_id cid, std::stringstream& program)
    {
        client_context& ctx = _clients.at(cid);
        auto stmt_col = interpreter::read(program);
        interpreter::run(stmt_col, ctx);
    }
}