#pragma once

#include <unordered_map>
#include <sstream>
#include <client_context.hpp>

#include "cmd_type.hpp"

namespace rvi::host
{
    typedef std::unordered_map<std::string, std::string> str_dictionary;

    struct parsed_stmt
    {
        cmd_type command;
        std::vector<std::string> args;
    };

    static std::vector<char> ignored_chars = {0, ' ', '\n', '\t', '\r'};

    class interpreter
    {
    private:
        static str_dictionary _global_vars;

        static const char SEP_LINE = ';';
        static const char SEP_CMDARGS = ':';
        static const char SEP_ARGS = ',';
        static const char TXT_ESC_CHAR = '"';
        static const char DEF_ESC_CHAR_BEGIN = '{';
        static const char DEF_ESC_CHAR_END = '}';

    public:
        static std::vector<parsed_stmt> read(std::stringstream& stream);
        static void filter_definitions(std::vector<parsed_stmt>& stmt_col);
        static void run(const std::vector<parsed_stmt>& lines, client_context& ctx);
        static std::stringstream clean_input(std::stringstream& sstr);

    private:

        static parsed_stmt parse_line(const std::string& line);
        static cmd_type parse_command(const std::string& txt);
        static void run_line(const parsed_stmt& line, client_context& ctx);
    };
}