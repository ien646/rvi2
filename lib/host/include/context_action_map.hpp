#pragma once

#include <unordered_map>
#include <functional>

#include <client_context.hpp>
#include <instruction_generator.hpp>

#include "cmd_type.hpp"
#include "cmd_map.hpp"
#include "interpreter.hpp"
#include "str_utils.hpp"

namespace rvi::host
{
    typedef std::function<void(client_context&, const std::vector<std::string>&)> ctx_action;

    void expect_argc(const std::vector<std::string>& args, int argc, cmd_type ct)
    {
        if(args.size() < argc)
        {
            auto cmd_name = get_cmd_name(ct);
            throw std::logic_error("Insufficient argument count for command: " + cmd_name);
        }
    }

    constexpr void no_expect_args() { return; }

    std::vector<definition_inst> parse_definition_body(const std::string& body);

    std::unordered_map<cmd_type, ctx_action> context_action_map = 
    {
        { 
            cmd_type::SELECT_FRAME , [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 1, cmd_type::SELECT_FRAME);
                std::string frame_name = args[0];
                ctx.select_frame(frame_name);
            }
        },
        {
            cmd_type::RELEASE_FRAME, [](client_context& ctx, const std::vector<std::string>&)
            {
                no_expect_args();
                ctx.release_frame();
            }
        },
        {
            cmd_type::DELETE_FRAME, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 1, cmd_type::DELETE_FRAME);
                std::string frame_name = args[0];
                ctx.delete_frame(frame_name);
            }
        },
        {
            cmd_type::DRAW_LINE, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 4, cmd_type::DRAW_LINE);
                float fx = std::stof(args[0]);
                float fy = std::stof(args[1]);
                float tx = std::stof(args[2]);
                float ty = std::stof(args[3]);
                vector2 from(fx, fy);
                vector2 to(tx, ty);
                ctx.draw_line(from, to);
            }
        },
        {
            cmd_type::SET_TRANSFORM, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 5, cmd_type::SET_TRANSFORM);
                float pos_x = std::stof(args[0]);
                float pos_y = std::stof(args[1]);
                float scl_x = std::stof(args[2]);
                float scl_y = std::stof(args[3]);
                float rottn = std::stof(args[4]);
                transform2 tform(vector2(pos_x, pos_y), vector2(scl_x, scl_y), rottn);
                ctx.set_transform(tform);
            }
        },
        {
            cmd_type::SET_POSITION, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 2, cmd_type::SET_POSITION);
                float pos_x = std::stof(args[0]);
                float pos_y = std::stof(args[1]);
                ctx.set_position(vector2(pos_x, pos_y));
            },
        },
        {
            cmd_type::SET_SCALE, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 2, cmd_type::SET_SCALE);
                float scl_x = std::stof(args[0]);
                float scl_y = std::stof(args[1]);
                ctx.set_scale(vector2(scl_x, scl_y));
            }
        },
        {
            cmd_type::SET_ROTATION, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 1, cmd_type::SET_ROTATION);
                float rottn = std::stof(args[0]);
                ctx.set_rotation(rottn);
            }
        },
        {
            cmd_type::SET_COLOR, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 4, cmd_type::SET_COLOR);
                uint8_t r = static_cast<uint8_t>(std::stoi(args[0]));
                uint8_t g = static_cast<uint8_t>(std::stoi(args[1]));
                uint8_t b = static_cast<uint8_t>(std::stoi(args[2]));
                uint8_t a = static_cast<uint8_t>(std::stoi(args[3]));
                ctx.set_color(color_rgba(r, b, g, a));
            }
        },
        {
            cmd_type::DEFINE, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 2, cmd_type::DEFINE);
                std::string name = args[0];
                std::string body = str_split(args[1], '{')[1];
                body = str_split(body, '}')[0];
                auto instructions = parse_definition_body(body);
                definition def(name);
                std::for_each(instructions.begin(), instructions.end(), [&](auto&& inst)
                { 
                    def.add_instruction(std::move(inst));
                });
                ctx.add_definition(std::move(def));
            }
        },
        {
            cmd_type::UNDEFINE, [](client_context& ctx, const std::vector<std::string>& args)
            {
                expect_argc(args, 1, cmd_type::UNDEFINE);
                std::string fname = args[0];
                ctx.delete_definition(fname);
            }
        }
    };    
}