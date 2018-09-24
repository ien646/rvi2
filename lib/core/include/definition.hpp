#pragma once

#include <utility>
#include <functional>
#include <vector>
#include <queue>
#include <string>

#include "rvi_base.hpp"

namespace rvi
{
    class client_context;   

    class definition
    {
    private:
        std::vector<definition_inst> _inst_seq;
        std::string _name;

    public:
        definition() = delete;
        definition(const std::string& name);
        definition(std::string&& name) noexcept;

        void add_instruction(definition_inst&& inst);
        void clear() noexcept;
        void execute_on_context(client_context& cCtx);

        const std::string& name() const noexcept;

        const std::vector<definition_inst>& get_sequence();
    };
}