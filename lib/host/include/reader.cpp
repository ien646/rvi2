#include "reader.hpp"

#include <cctype>
#include <vector>

#include <rvi_assert.hpp>

namespace rvi
{
    struct preprocess_state
    {
        bool primary_escape = false;
        bool secondary_escape = false;
    };

    static void toggle(bool& flag)
    {
        flag = !flag;
    }

    static void check_def_end_state(preprocess_state& state)
    {
        rvi_assert(
            !state.primary_escape,
            "expected end character of primary escape sequence"
        );
        rvi_assert(
            !state.secondary_escape,
            "expected end character of secondary escape sequence"
        );
    }

    static void check_def_end_stacksz(std::vector<preprocess_state>& stack)
    {
        rvi_assert(stack.size() > 1, "unexpected end of definition escape sequence!");
    }

    reader::reader(std::basic_iostream<char>& stream)
        : _stream(stream)
    { }

    std::vector<rvi::parsed_stmt> reader::parse()
    {
        std::stringstream pp_stream = preprocess();
    }

    std::stringstream reader::preprocess()
    {
        std::stringstream result;

        // -- State stack --
        std::vector<preprocess_state> state_stack;
        state_stack.push_back(preprocess_state());              

        char ch;
        while (_stream >> ch)
        {            
            auto& current_state = state_stack.top();

            switch (ch)
            {
            case PRIMARY_ESCAPE_CH:
                toggle(current_state.primary_escape);
                break;

            case SECONDARY_ESCAPE_CH:
                toggle(current_state.secondary_escape);
                break;

            case DEFINITION_ESCAPE_BEG_CH:
                state_stack.push_back(preprocess_state());
                break;

            case DEFINITION_ESCAPE_END_CH:
                check_def_end_stacksz(state_stack);
                check_def_end_state(current_state);
                state_stack.pop_back();
                break;

            default:
                if (current_state.primary_escape || current_state.secondary_escape)
                {
                    result << ch;
                }
                else
                {
                    if (!is_ignored_char(ch))
                    {
                        result << ch;
                    }
                }
                break;                           
            }
        }       
        _stream_cleared = true;
        return result;
    }

    bool reader::is_ignored_char(char ch)
    {
        if (std::iscntrl(ch))
        {
            return false;
        }

        auto it_found = std::find(
            reader_ignored_chars.begin(),
            reader_ignored_chars.end(),
            ch
        );

        return it_found != reader_ignored_chars.end();
    }
}