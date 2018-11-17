#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <cmd_map.hpp>

namespace rvi
{
    struct parsed_stmt
    {
        cmd_type cmd;
        std::string args;
    };

    static const std::vector<char> reader_ignored_chars = 
    {
        '\n',
        '\r',
        '\t',
        '\0',
        ' '
    };

    static const char PRIMARY_ESCAPE_CH = '\"';
    static const char SECONDARY_ESCAPE_CH = '\'';
    static const char DEFINITION_ESCAPE_BEG_CH = '{';
    static const char DEFINITION_ESCAPE_END_CH = '}';

    class reader
    {
    private:
        std::basic_iostream<char>& _stream;
        bool _stream_cleared = false;

    public:
        reader() = delete;
        reader(std::basic_iostream<char>& stream);

        std::vector<parsed_stmt> parse();

    private:
        std::stringstream preprocess();
        bool is_ignored_char(char ch);
    };
}