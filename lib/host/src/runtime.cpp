#include "runtime.hpp"

#include "interpreter.hpp"

using namespace rvi::serialization;

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

    cmdlist_t runtime::get_update_commands(client_id cid)
    {
        std::vector<std::vector<std::uint8_t>> result;

        client_context& ctx = _clients.at(cid);
        auto line_map = ctx.snapshot_diff_relative();

        for (const auto& data_pair : line_map)
        {
            const std::string& fname = data_pair.first;
            const auto& lines = data_pair.second;

            // select frame commands
            const auto path = str_split(fname, client_context::FRAMEPATH_SEPARATOR);

            for (auto it = path.begin(); it != path.end(); it++)
            {
                result.push_back(serializer::select_frame(*it));
            }            

            // lines
            for (auto& line : lines)
            {
                result.push_back(serializer::draw_line(line));
            }
            
            // release frame commands
            for (size_t i = 0; i < path.size(); i++)
            {
                result.push_back(serializer::release_frame());
            }
        }

        return result;
    }
}