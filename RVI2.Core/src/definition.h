#pragma once

#include <utility>
#include <functional>
#include <vector>
#include <queue>

namespace rvi
{
    class ClientContext;

    class Definition
    {
    public:
        typedef std::function<void(ClientContext&)> Instruction;

    private:
        std::vector<Instruction> _instSequence;
        std::string _name;
        
    public:
        Definition() = delete;
        Definition(const std::string& name);
        Definition(std::string&& name);

        void AddInstruction(Instruction&& inst);
        void Clear();
        void ExecuteOnContext(ClientContext& cCtx);
    };
}