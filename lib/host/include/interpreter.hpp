#pragma once

#include <unordered_map>
#include <sstream>
#include <client_context.hpp>

namespace rvi::host
{
    typedef std::unordered_map<std::string, std::string> str_dictionary;

    enum class command_type
    {
        INVALID_CMD,

        SELECT_FRAME,
        RELEASE_FRAME,
        DELETE_FRAME,
        DRAW_LINE,
        SET_COLOR,
        SET_TRANSFORM,
        SET_POSITION,
        SET_ROTATION,
        SET_SCALE,
        DEFINE,
        UNDEFINE        
    };    

    struct parsed_line
    {
        command_type command;
        std::vector<std::string> args;
    };

    std::vector<char> ignored_chars =
    {
        0,
        ' ',
        '\n',
        '\t',
        '\r'
    };    

    class interpreter
    {
    private:
        str_dictionary _global_vars;

        static const char SEP_LINE = ';';
        static const char SEP_CMDARGS = ':';
        static const char SEP_ARGS = ',';
        static const char TXT_ESC_CHAR = '"';

    public:
        std::vector<parsed_line> read(std::stringstream& stream);
        void run(const std::vector<parsed_line>& lines, client_context& ctx);
    private:

        parsed_line parse_line(const std::string& line);
        command_type parse_command(const std::string& txt);
        void run_line(const parsed_line& line, client_context& ctx);     
        std::stringstream clean_input(std::stringstream& sstr);
    };
}