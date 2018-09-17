#pragma once

#include <utility>
#include <functional>
#include <vector>
#include <queue>

namespace rvi
{
    class ClientContext;
    typedef std::function<void(ClientContext&)> DefinitionInstruction;

    class Definition
    {
    private:
        std::vector<DefinitionInstruction> _instSequence;
        std::string _name;

    public:
        Definition() = delete;
        Definition(const std::string& name);
        Definition(std::string&& name) noexcept;

        void AddInstruction(DefinitionInstruction&& inst);
        void Clear() noexcept;
        void ExecuteOnContext(ClientContext& cCtx);
    };
}