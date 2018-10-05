#include "instruction_generator.hpp"

#define CAPTURE_RVALUEREF(x) &x
#define NOCAPTURE

using std::string;

namespace rvi
{
    definition_inst instruction_generator::draw_line(vector2 from, vector2 to)
    {
        return[=](client_context& c)
        { c.draw_line(from, to); };
    }

    definition_inst instruction_generator::draw_line(vector2 from, color_rgba from_color, vector2 to, color_rgba to_color)
    {
        return[=](client_context& c)
        { c.draw_line(from, from_color, to, to_color); };
    }

    definition_inst instruction_generator::draw_line(vertex from, vertex to)
    {
        return[=](client_context& c)
        { c.draw_line(from, to); };
    }

    definition_inst instruction_generator::select_frame(const string& name)
    {
        return[=](client_context& c)
        { c.select_frame(name); };
    }

    definition_inst instruction_generator::select_frame(string&& name)
    {
        return[&](client_context& c)
        { c.select_frame(std::move(name)); };
    }

    definition_inst instruction_generator::release_frame()
    {
        return[NOCAPTURE](client_context& c)
        { c.release_frame(); };
    }

    definition_inst instruction_generator::delete_frame(const std::string& name)
    {
        return[&](client_context& c)
        { c.delete_frame(name); };
    }

    definition_inst instruction_generator::set_color(color_rgba color)
    {
        return[=](client_context& c) noexcept
        { c.set_color(color); };
    }

    definition_inst instruction_generator::set_transform(const transform2& tform)
    {
        return[=](client_context& c) noexcept
        { c.set_transform(tform); };
    }

    definition_inst instruction_generator::set_position(const vector2& pos)
    {
        return[&](client_context& c) noexcept
        { c.set_position(pos); };
    }

    definition_inst instruction_generator::set_scale(const vector2& scale)
    {
        return[&](client_context& c) noexcept
        { c.set_scale(scale); };
    }

    definition_inst instruction_generator::set_rotation(float angle)
    {
        return [&](client_context& c) noexcept
        { c.set_rotation(angle); };
    }

    definition_inst instruction_generator::set_transform(transform2&& tform)
    {
        return[&](client_context& c) noexcept
        { c.set_transform(std::move(tform)); };
    }

    definition_inst instruction_generator::add_definition(const definition& instruction)
    {
        return[instruction](client_context& c)
        { c.add_definition(instruction); };
    }

    definition_inst instruction_generator::add_definition(definition&& instruction)
    {
        return[CAPTURE_RVALUEREF(instruction)](client_context& c)
        { c.add_definition(std::move(instruction)); };
    }

    definition_inst instruction_generator::delete_definition(const std::string& def_name)
    {
        return[&](client_context& c)
        { c.delete_definition(def_name); };
    }

    definition_inst instruction_generator::execute_definition(const std::string& def_name)
    {
        return[&](client_context& c)
        { c.execute_definition(def_name); };
    }
}