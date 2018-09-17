#pragma once

#include "rvi_base.h"
#include "instruction_generator.h"

namespace rvi
{
    class Program
    {
    private:
        std::vector<DefinitionInstruction> _program;
    public:
        void AddInstruction(const DefinitionInstruction& inst);
        void AddInstruction(DefinitionInstruction&& inst);

        void ExecOnContext(ClientContext& ctx);
    };
}