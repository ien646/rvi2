#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include <cmd_type.hpp>

namespace rvi
{
    struct parsed_stmt
    {
        cmd_type cmd;
        std::vector<std::string> args;
    };

    struct processing_state
    {
        std::stringstream cmd;
        std::stringstream args;
        bool past_cmd = false;
        int str_escape = 0;
    };  

    class reader
    {
    private:
        std::basic_istream<char>& _stream;
        static const char INSTRUCTION_SEP_CH;
        static const char CMDARGS_SEP_CH;
        static const char ARGUMENTS_SEP_CH;
        static const char STRING_ESC_CH_BEG;
        static const char STRING_ESC_CH_END;
        static const std::unordered_set<char> IGNORED_CHARS;

    public:
        reader(std::basic_istream<char>& stream);
        std::vector<parsed_stmt> process();

    private:
        void handle_instruction_separator(processing_state& state, std::vector<parsed_stmt>& result);
        void handle_cmdargs_separator(processing_state& state, std::vector<parsed_stmt>& result);
        void handle_string_beg_token(processing_state& state);
        void handle_string_end_token(processing_state& state);
        void handle_character(processing_state& state, char ch);
        parsed_stmt parse_state(processing_state& state);
        std::vector<std::string> parse_arg_str(std::string_view arg_str);
        void push_char_uncond(processing_state& state, char ch);
        bool is_ignored_char(char ch);
    };
}