#pragma once

#include <utility>
#include <functional>
#include <vector>
#include <queue>
#include <string>

#include "rvi_base.hpp"

namespace rvi
{
    class ClientContext;   

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

        const std::string& Name() const noexcept;

        const std::vector<DefinitionInstruction>& GetSequence();
    };
}