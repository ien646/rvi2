#pragma once

#include <unordered_map>
#include <functional>
#include <fstream>
#include <iostream>

#include <client_context.hpp>

#include "cmd_type.hpp"
#include "cmd_map.hpp"
#include "interpreter.hpp"
#include "str_utils.hpp"
#include "data_reader.hpp"
#include "runtime.hpp"
#include "definition.hpp"
#include "host_types.hpp"

namespace rvi::host
{
    extern void expect_argc(const arglist_t& args, size_t argc, cmd_type ct);

    static constexpr void no_expect_args() { return; }

    extern definition parse_definition_body(const std::string& body);

    static std::unordered_map<cmd_type, runtime_inst_t> context_action_map = 
    {
        { 
            cmd_type::SELECT_FRAME , [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::SELECT_FRAME);
                std::string frame_name = args[0];
                rt.get_client(cid)->select_frame(frame_name);
            }
        },
        {
            cmd_type::RELEASE_FRAME, [](cid_t cid, runtime& rt, const arglist_t&)
            {
                no_expect_args();
                rt.get_client(cid)->release_frame();
            }
        },
        {
            cmd_type::DELETE_FRAME, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::DELETE_FRAME);
                std::string frame_name = args[0];
                rt.get_client(cid)->delete_frame(frame_name);
            }
        },
        {
            cmd_type::DRAW_LINE, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 4, cmd_type::DRAW_LINE);
                float fx = std::stof(args[0]);
                float fy = std::stof(args[1]);
                float tx = std::stof(args[2]);
                float ty = std::stof(args[3]);
                vector2 from(fx, fy);
                vector2 to(tx, ty);
                rt.get_client(cid)->draw_line(from, to);
            }
        },
        {
            cmd_type::SET_TRANSFORM, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 5, cmd_type::SET_TRANSFORM);
                float pos_x = std::stof(args[0]);
                float pos_y = std::stof(args[1]);
                float scl_x = std::stof(args[2]);
                float scl_y = std::stof(args[3]);
                float rottn = std::stof(args[4]);
                transform2 tform(vector2(pos_x, pos_y), vector2(scl_x, scl_y), rottn);
                rt.get_client(cid)->set_transform(tform);
            }
        },
        {
            cmd_type::SET_POSITION, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 2, cmd_type::SET_POSITION);
                float pos_x = std::stof(args[0]);
                float pos_y = std::stof(args[1]);
                rt.get_client(cid)->set_position(vector2(pos_x, pos_y));
            },
        },
        {
            cmd_type::SET_SCALE, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 2, cmd_type::SET_SCALE);
                float scl_x = std::stof(args[0]);
                float scl_y = std::stof(args[1]);
                rt.get_client(cid)->set_scale(vector2(scl_x, scl_y));
            }
        },
        {
            cmd_type::SET_ROTATION, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::SET_ROTATION);
                float rottn = std::stof(args[0]);
                rt.get_client(cid)->set_rotation(rottn);
            }
        },
        {
            cmd_type::SET_COLOR, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 4, cmd_type::SET_COLOR);
                uint8_t r = static_cast<uint8_t>(std::stoi(args[0]));
                uint8_t g = static_cast<uint8_t>(std::stoi(args[1]));
                uint8_t b = static_cast<uint8_t>(std::stoi(args[2]));
                uint8_t a = static_cast<uint8_t>(std::stoi(args[3]));
                rt.get_client(cid)->set_color(color_rgba(r, b, g, a));
            }
        },
        {
            cmd_type::DEFINE, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 2, cmd_type::DEFINE);
                std::string name = args[0];
                std::string body = str_split(args[1], '{')[1];
                body = str_split(body, '}')[0];  
                rt.add_definition(cid, name, parse_definition_body(body));
            }
        },
        {
            cmd_type::UNDEFINE, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::UNDEFINE);
                std::string fname = args[0];
                rt.delete_definition(cid, fname);
            }
        },
        {
            cmd_type::CALL, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::CALL);
                std::string fname = args[0];
                rt.execute_definition(cid, fname);
            }
        },
        {
            cmd_type::INCLUDE, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::INCLUDE);
                const std::string& fname = args[0];
                if(rt.can_include(cid, fname))
                {
                    std::string text = data_reader::get_include_text(fname);
                    std::stringstream ss;
                    ss << text;
                    auto stmt_col = interpreter::read(ss);

                    std::string aux = rt.current_include(cid);
                    rt.push_include(cid, fname);
                    client_context& ctx = *(rt.get_client(cid));
                    interpreter::run(cid, rt, stmt_col);
                    rt.pop_include(cid);
                }
                else
                {
                    std::cout << "Skipping re-inclusion of file: [ " << fname << " ]" << std::endl;
                }
            }
        },
        {
            cmd_type::NO_REINCLUDE, [](cid_t cid, runtime& rt, const arglist_t&)
            {
                no_expect_args();
                rt.mark_include_once(cid);
            }
        },
        {
            cmd_type::EXEC_BIND, [](cid_t cid, runtime& rt, const arglist_t& args)
            {
                expect_argc(args, 1, cmd_type::EXEC_BIND);
                std::string name = args[0];
                arglist_t b_args(args.begin() + 1, args.end());
                rt.exec_binding(cid, name, b_args);
            }
        }
    };
}