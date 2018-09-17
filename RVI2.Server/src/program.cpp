#include "program.h"

namespace rvi
{
    void Program::AddInstruction(const DefinitionInstruction& inst)
    {
        _program.push_back(inst);
    }

    void Program::AddInstruction(DefinitionInstruction&& inst)
    {
        _program.push_back(std::move(inst));
    }

    void Program::ExecOnContext(ClientContext& ctx)
    {
        for (DefinitionInstruction& di : _program)
        {
            di(ctx);
        }
    }
}