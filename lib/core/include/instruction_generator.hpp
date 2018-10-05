#pragma once

#include "client_context.hpp"
#include "definition.hpp"

namespace rvi
{
    class instruction_generator
    {
    public:       

        static definition_inst draw_line(vector2 from, vector2 to);
        static definition_inst draw_line(vector2 from, color_rgba fromColor, vector2 to, color_rgba toColor);
        static definition_inst draw_line(vertex from, vertex to);

        static definition_inst select_frame(const std::string& name);
        static definition_inst select_frame(std::string&& name);

        static definition_inst release_frame();

        static definition_inst delete_frame(const std::string& name);

        static definition_inst set_color(color_rgba color);

        static definition_inst set_transform(const transform2& tform);
        static definition_inst set_transform(transform2&& tform);

        static definition_inst set_position(const vector2& pos);
        static definition_inst set_scale(const vector2& scale);
        static definition_inst set_rotation(float angle);
        
        static definition_inst add_definition(const definition& instruction);
        static definition_inst add_definition(definition&& instruction);

        static definition_inst delete_definition(const std::string& def_name);

        static definition_inst execute_definition(const std::string& def_name);
    };
}