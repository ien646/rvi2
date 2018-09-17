#include "interpreter.h"

namespace rvi
{
    void Interpreter::ParseProgram(std::stringstream& sstr, Program& program)
    {
        std::string line;
        while (std::getline(sstr, line, DELIM))
        {
            ParseLine(line, program);
        }
    }

    void Interpreter::ParseLine(const std::string& line, Program& program)
    {
        std::string command;
        std::vector<std::string> parameters;

        std::string cleanLine = CleanLine(line);
        std::stringstream sstr;
        sstr.str(cleanLine);

        // -- Command --
        std::getline(sstr, command, '(');

        // -- Params --
        std::string param;
        bool paramOk = false;
        char auxc = 0;
        bool betweenDq = false;
        while (sstr.get(auxc))
        {
            if (auxc == ',')
            {
                parameters.push_back(param);
                param.clear();
                paramOk = true;
            }
            else if (auxc == ')')
            {
                if (paramOk)
                {
                    parameters.push_back(param);
                    param.clear();
                }
                break;
            }
            else
            {
                param += auxc;
                paramOk = true;
            }
        }

        program.AddInstruction(InterpretText(command, parameters));
    }

    std::string Interpreter::CleanLine(const std::string& line)
    {
        std::string result;

        bool betweenDoubleQuotes = false;
        for (char c : line)
        {
            if (c == '"')
            {
                betweenDoubleQuotes = !betweenDoubleQuotes;
            }
            else
            {
                if (betweenDoubleQuotes)
                {
                    result += c;
                }
                else
                {
                    if (IsCharValid(c))
                    {
                        result += c;
                    }
                }
            }
        }

        return result;
    }

    bool Interpreter::IsCharValid(char c)
    {
        return !(c < 32 || c == 127 || c == ' ');
    }

    DefinitionInstruction Interpreter::InterpretText(const std::string& command, const std::vector<std::string>& params)
    {
        if (command == "draw_line")
        {
            return IT_DrawLine(params);
        }
        else
        {
            return [](ClientContext& cctx) { return; };
        }
    }

    DefinitionInstruction Interpreter::IT_DrawLine(const std::vector<std::string>& params)
    {
        assert(params.size() >= 4);

        float from_x = std::stof(params[0]);
        float from_y = std::stof(params[1]);
        float to_x = std::stof(params[2]);
        float to_y = std::stof(params[3]);
        Vector2 vfrom(from_x, from_y);
        Vector2 vto(to_x, to_y);

        return InstructionGenerator::DrawLine(vfrom, vto);
    }
}