#include "interpreter.hpp"

#include <algorithm>
#include <cctype>
#include <cinttypes>

#include "str_utils.hpp"
#include "cmd_type.hpp"
#include "cmd_map.hpp"

namespace rvi::host
{
    bool is_ignored_ch(char ch)
    {
        return std::find(ignored_chars.begin(), ignored_chars.end(), ch) != ignored_chars.end();
    }

    std::stringstream interpreter::clean_input(std::stringstream& sstr)
    {
        std::stringstream result;
        bool dq_escape = false;
        for(char ch; sstr >> ch;) 
        {
            // Double quotes escaping
            if (ch == TXT_ESC_CHAR)
            {
                dq_escape = !dq_escape;
            }

            if(!is_ignored_ch(ch) || dq_escape)
            {
                result << ch;
            }
        }
        return result;
    }

    cmd_type interpreter::parse_command(const std::string& txt)
    {
        std::string lower_txt = txt;
        str_tolower(lower_txt);
        if(cmd_map.count(lower_txt) > 0)
        {
            return cmd_map.at(lower_txt);
        }
        else
        {
            return cmd_type::INVALID_CMD;
        }
    }

    std::vector<parsed_stmt> interpreter::read(std::stringstream& stream)
    {
        std::vector<parsed_stmt> result;
        auto clean_text = clean_input(stream);

        std::string line;
        while(std::getline(clean_text, line, SEP_LINE))
        {
            result.push_back(parse_line(line));
        }
        return result;
    }

    parsed_stmt interpreter::parse_line(const std::string& line)
    {
        parsed_stmt result;

        auto segments = str_split(line, SEP_CMDARGS);
        if (segments.size() != 2)
        {            
            throw std::logic_error("Invalid line syntax: " + line);
        }
        
        result.command = parse_command(segments[0]);

        auto args = str_split(segments[1], SEP_ARGS);
        std::move(args.begin(), args.end(), std::back_inserter(result.args));

        return result;
    }

    void interpreter::run(const std::vector<parsed_stmt>& lines, client_context& ctx)
    {
        for (auto& line : lines)
        {
            run_line(line, ctx);
        }
    }

    void interpreter::run_line(const parsed_stmt& line, client_context& ctx)
    {
        //...
    }
}