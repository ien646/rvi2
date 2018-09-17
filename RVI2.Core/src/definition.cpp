#include "definition.h"

namespace rvi
{
    Definition::Definition(const std::string& name)
        : _name(name)
    { }

    Definition::Definition(std::string&& name) noexcept
        : _name(std::move(name))
    { }

    void Definition::AddInstruction(Instruction&& inst)
    {
        _instSequence.push_back(std::move(inst));
    }

    void Definition::Clear() noexcept
    {
        _instSequence.clear();
    }

    void Definition::ExecuteOnContext(ClientContext& clientContext)
    {
        for (const Instruction& inst : _instSequence)
        {
            inst(clientContext);
        }
    }
}