#include "interpreter.hpp"

#include <algorithm>
#include <cctype>
#include <cinttypes>

#include "str_utils.hpp"

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

    command_type interpreter::parse_command(const std::string& txt)
    {
        std::string copy = txt;
        str_tolower(copy);
        if (copy == "select_frame")
            return command_type::SELECT_FRAME;

        else if (copy == "release_frame")
            return command_type::RELEASE_FRAME;

        else if (copy == "delete_frame")
            return command_type::DELETE_FRAME;

        else if (copy == "draw_line")
            return command_type::DRAW_LINE;

        else if (copy == "set_color")
            return command_type::SET_COLOR;

        else if (copy == "set_transform")
            return command_type::SET_TRANSFORM;

        else if (copy == "set_position")
            return command_type::SET_POSITION;

        else if (copy == "set_scale")
            return command_type::SET_SCALE;

        else if (copy == "set_rotation")
            return command_type::SET_ROTATION;

        else if (copy == "define")
            return command_type::DEFINE;

        else if (copy == "undefine")
            return command_type::UNDEFINE;

        else
            return command_type::INVALID_CMD;
    }

    std::vector<parsed_line> interpreter::read(std::stringstream& stream)
    {
        std::vector<parsed_line> result;
        auto clean_text = clean_input(stream);

        std::string line;
        while(std::getline(clean_text, line, SEP_LINE))
        {
            result.push_back(parse_line(line));
        }
        return result;
    }

    parsed_line interpreter::parse_line(const std::string& line)
    {
        parsed_line result;

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

    void interpreter::run(const std::vector<parsed_line>& lines, client_context& ctx)
    {
        for (auto& line : lines)
        {
            run_line(line, ctx);
        }
    }

    void interpreter::run_line(const parsed_line& line, client_context& ctx)
    {
        //...
    }
}