#pragma once

#include <unordered_map>
#include <sstream>
#include <client_context.hpp>

#include "cmd_type.hpp"

namespace rvi::host
{
    typedef int cid_t;

    class runtime; // FWD DECL
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
        static void run(cid_t cid, runtime& rtime, const std::vector<parsed_stmt>& lines);
        static std::stringstream clean_input(std::stringstream& sstr);

    private:

        static parsed_stmt parse_line(const std::string& line);
        static cmd_type parse_command(const std::string& txt);
        static void run_line(cid_t cid, runtime& rtime, const parsed_stmt& line);
    };
}