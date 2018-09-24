#include "definition.hpp"

namespace rvi
{
    definition::definition(const std::string& name)
        : _name(name)
    { }

    definition::definition(std::string&& name) noexcept
        : _name(std::move(name))
    { }

    void definition::add_instruction(definition_inst&& inst)
    {
        _inst_seq.push_back(std::move(inst));
    }

    void definition::clear() noexcept
    {
        _inst_seq.clear();
    }

    void definition::execute_on_context(client_context& ctx)
    {
        for (const definition_inst& inst : _inst_seq)
        {
            inst(ctx);
        }
    }

    const std::string& definition::name() const noexcept
    {
        return _name;
    }

    const std::vector<definition_inst>& definition::get_sequence()
    {
        return _inst_seq;
    }
}