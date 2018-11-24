#include "reader.hpp"

#include <sstream>
#include <algorithm>
#include <cstdio>

#include <cmd_map.hpp>
#include <rvi_assert.hpp>
#include <str_utils.hpp>

namespace rvi
{
    const char reader::INSTRUCTION_SEP_CH = ';';
    const char reader::CMDARGS_SEP_CH = ':';
    const char reader::ARGUMENTS_SEP_CH = ',';
    const char reader::STRING_ESC_CH_BEG = '{';
    const char reader::STRING_ESC_CH_END = '}';
    const std::unordered_set<char> reader::IGNORED_CHARS = { ' ', '\r', '\n', '\t' };    
      

    reader::reader(std::basic_istream<char>& stream)
        : _stream(stream)
    {
        _stream >> std::noskipws;
    }

    std::vector<parsed_stmt> reader::process()
    {
        std::vector<parsed_stmt> result;
        processing_state current_state;

        char ch;
        while(_stream >> ch)
        {
            switch (ch)
            {
                case INSTRUCTION_SEP_CH:
                    handle_instruction_separator(current_state, result);
                    break;
                case CMDARGS_SEP_CH:
                    handle_cmdargs_separator(current_state);
                    break;
                case STRING_ESC_CH_BEG:
                    handle_string_beg_token(current_state);
                    break;
                case STRING_ESC_CH_END:
                    handle_string_end_token(current_state);
                    break;
                default:
                    handle_character(current_state, ch);
                    break;
            }
        }

        return result;
    }

    void reader::push_char_uncond(processing_state& state, char ch)
    {
        if(!state.past_cmd)
        {
            state.cmd << ch;
        }
        else
        {
            state.args << ch;
        }
    }

    void reader::handle_instruction_separator(processing_state& state, std::vector<parsed_stmt>& result)
    {
        if(state.str_escape > 0)
        {
            push_char_uncond(state, INSTRUCTION_SEP_CH);
        }
        else
        {
            result.push_back(parse_state(state));
            state = processing_state();
        }
    }

    parsed_stmt reader::parse_state(processing_state& state)
    {
        parsed_stmt result;
        std::string cmd_str = state.cmd.str();

        rvi_assert(
            cmd_map.count(cmd_str) > 0,
            "Command '" + cmd_str + "' is not a valid command!"
        );

        result.cmd = cmd_map.at(state.cmd.str());
        if(state.past_cmd)
        {
            result.args = parse_arg_str(state.args.str());
        }

        return result;
    }

    void reader::handle_cmdargs_separator(processing_state& state)
    {
        rvi_assert(
            state.str_escape > 0 || !state.past_cmd,
            "Unexpected cmd-args separator character!"
        );
        if(state.str_escape > 0)
        {
            push_char_uncond(state, CMDARGS_SEP_CH);
        }
        else
        {
            state.past_cmd = true;
        }
    }

    void reader::handle_string_beg_token(processing_state& state)
    {
        if(state.str_escape > 0)
        {
            push_char_uncond(state, STRING_ESC_CH_BEG);
        }
        state.str_escape++;
    }

    void reader::handle_string_end_token(processing_state& state)
    {
        rvi_assert(
            state.str_escape > 0,
            "Unexpected end of string escape sequence!"
        );

        state.str_escape--;
        if(state.str_escape > 0)
        {
            push_char_uncond(state, STRING_ESC_CH_END);
        }
    }

    void reader::handle_character(processing_state& state, char ch)
    {
        if(state.str_escape > 0)
        {
            if(ch == ARGUMENTS_SEP_CH)
            {
                push_char_uncond(state, 0x06);
            }
            else
            {
                push_char_uncond(state, ch);
            }
        }
        else
        {
            if(!is_ignored_char(ch))
            {
                push_char_uncond(state, ch);
            }
        }
    }

    bool reader::is_ignored_char(char ch)
    {
        return std::iscntrl(ch) || (IGNORED_CHARS.count(ch) > 0);
    }

    std::vector<std::string> reader::parse_arg_str(std::string_view arg_str)
    {
        std::vector<std::string> result = str_utils::split(arg_str, ARGUMENTS_SEP_CH);
        for(auto& str : result)
        {
            str = str_utils::replace(str, 0x06, ',');
        }
        return result;
    }
}