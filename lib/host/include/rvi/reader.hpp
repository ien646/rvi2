#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

#include <rvi/command_type.hpp>
#include <rvi/parsed_stmt.hpp>
#include <rvi/constrained_buffer.hpp>

namespace rvi
{
    struct reader_parse_state
    {
        std::stringstream cmd;
        std::stringstream args;
        bool past_cmd = false;
        int str_escape = 0;
        bool comment = false;
        constrained_buffer<char, 3> buffer;
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
        static const std::string COMMENT_SEQ_STR;

    public:
        reader(std::basic_istream<char>& stream);
        std::vector<parsed_stmt> process();

    private:
        void handle_instruction_separator(reader_parse_state& state, std::vector<parsed_stmt>& result);
        void handle_cmdargs_separator(reader_parse_state& state);
        void handle_string_beg_token(reader_parse_state& state);
        void handle_string_end_token(reader_parse_state& state);
        void handle_character(reader_parse_state& state, char ch);
        parsed_stmt parse_state(reader_parse_state& state);
        std::vector<std::string> parse_arg_str(std::string_view arg_str);
        void push_char_uncond(reader_parse_state& state, char ch);
        bool is_ignored_char(char ch);
    };
}