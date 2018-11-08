#include "context_action_map.hpp"

namespace rvi::host
{
    void expect_argc(const arglist_t& args, size_t argc, cmd_type ct)
    {
        if (args.size() < argc)
        {
            auto cmd_name = get_cmd_name(ct);
            throw std::logic_error("Insufficient argument count for command: " + cmd_name);
        }
    }    

    definition parse_definition_body(const std::string& body)
    {
        definition result;

        std::stringstream ss_body(body);
        std::stringstream ss_clean_body = interpreter::clean_input(ss_body);

        auto lines = interpreter::read(ss_clean_body);
        for (auto& line : lines)
        {
            definition_line defline;
            defline.cmd = get_cmd_name(line.command);
            defline.args = line.args;
            result.lines.push_back(std::move(defline));
        }
        return result;
    }
}