#include "context_action_map.hpp"

namespace rvi::host
{
    void i_select_frame(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 1, cmd_type::SELECT_FRAME);
        result.push_back(instruction_generator::select_frame(line.args[0]));
    }

    void i_release_frame(const parsed_stmt&, std::vector<definition_inst>& result)
    {
        no_expect_args();
        result.push_back(instruction_generator::release_frame());
    }

    void i_delete_frame(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 1, cmd_type::DELETE_FRAME);
        result.push_back(instruction_generator::delete_frame(line.args[0]));
    }

    void i_draw_line(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 4, cmd_type::DRAW_LINE);
        float fx = std::stof(line.args[0]);
        float fy = std::stof(line.args[1]);
        float tx = std::stof(line.args[2]);
        float ty = std::stof(line.args[3]);
        vector2 from(fx, fy);
        vector2 to(tx, ty);
        result.push_back(instruction_generator::draw_line(from, to));
    }

    void i_set_transform(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 5, cmd_type::SET_TRANSFORM);
        float px = std::stof(line.args[0]);
        float py = std::stof(line.args[1]);
        float sx = std::stof(line.args[2]);
        float sy = std::stof(line.args[3]);
        float rt = std::stof(line.args[4]);
        transform2 tform(vector2(px, py), vector2(sx, sy), rt);
        result.push_back(instruction_generator::set_transform(std::move(tform)));
    }

    void i_set_position(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 2, cmd_type::SET_POSITION);
        float px = std::stof(line.args[0]);
        float py = std::stof(line.args[1]);
        result.push_back(instruction_generator::set_position(vector2(px, py)));
    }

    void i_set_scale(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 2, cmd_type::SET_SCALE);
        float sx = std::stof(line.args[0]);
        float sy = std::stof(line.args[1]);
        result.push_back(instruction_generator::set_position(vector2(sx, sy)));
    }

    void i_set_rotation(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 1, cmd_type::SET_ROTATION);
        float rt = std::stof(line.args[0]);
        result.push_back(instruction_generator::set_rotation(rt));
    }

    void i_define(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 2, cmd_type::DEFINE);
        std::string def_name = line.args[0];
        auto instructions = parse_definition_body(line.args[1]);
        definition def(def_name);
        for(auto&& inst : instructions)
        {
            def.add_instruction(std::move(inst));
        }
        result.push_back(instruction_generator::add_definition(std::move(def)));
    }

    void i_undefine(const parsed_stmt& line, std::vector<definition_inst>& result)
    {
        expect_argc(line.args, 1, cmd_type::UNDEFINE);
        std::string def_name = line.args[0];
        result.push_back(instruction_generator::delete_definition(def_name));
    }

    std::vector<definition_inst> parse_definition_body(const std::string& body)
    {
        std::vector<definition_inst> result;
        auto stream = std::stringstream(body);
        auto lines = interpreter::read(stream);
        for(auto& line : lines)
        {
            switch(line.command)
            {
                case cmd_type::SELECT_FRAME:
                {
                    i_select_frame(line, result);
                    break;
                }
                case cmd_type::RELEASE_FRAME:
                {
                    i_release_frame(line, result);
                    break;
                }
                case cmd_type::DELETE_FRAME:
                {
                    i_delete_frame(line, result);
                    break;
                }
                case cmd_type::DRAW_LINE:
                {
                    i_draw_line(line, result);
                    break;
                }
                case cmd_type::SET_TRANSFORM:
                {
                    i_set_transform(line, result);
                    break;
                }
                case cmd_type::SET_POSITION:
                {
                    i_set_position(line, result);
                    break;
                }
                case cmd_type::SET_SCALE:
                {
                    i_set_scale(line, result);
                    break;
                }
                case cmd_type::SET_ROTATION:
                {
                    i_set_rotation(line, result);
                    break;
                }
                case cmd_type::DEFINE:
                {
                    i_define(line, result);
                    break;
                }
                case cmd_type::UNDEFINE:
                {
                    i_undefine(line, result);
                    break;
                }
            }
        }
        return result;
    }
}