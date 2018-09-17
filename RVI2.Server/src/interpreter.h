#pragma once

#include <array>
#include <memory>

#include "rvi_base.h"
#include "instruction_generator.h"
#include "definition.h"
#include "session.h"

namespace rvi
{
    class Interpreter
    {
    private:
        const static char DELIM = ';';

    public:
        static void ParseProgram(std::stringstream& sstr, Program& program);

    private:
        static void ParseLine(const std::string& line, Program& program);
        static std::string CleanLine(const std::string& line);
        static bool IsCharValid(char c);
        static DefinitionInstruction InterpretText(const std::string& command, const std::vector<std::string>& params);

        static DefinitionInstruction IT_DrawLine(const std::vector<std::string>& params);
    };
}