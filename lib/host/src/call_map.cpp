#include "call_map.hpp"

#include <fstream>

#include <client_instance.hpp>
#include <runtime.hpp>
#include <rvi_assert.hpp>

#include "reader.hpp"
#include "parsed_stmt.hpp"

#define RT_CALL_ENTRY(name) \
    void name(client_instance& c_inst, const arglist_t& args)

#define STR(v) std::to_string(v)

namespace rvi
{
    // -- HELPER METHODS --
    void expect_argc(const arglist_t& args, int count)
    {
        rvi_assert(
            args.size() >= count,
            "Expected argument count of " 
                + STR(count) 
                + "; Actual arg count: " 
                + STR(args.size())
        );
    }
    // --------------------

    // -- FWD DECLARE --
    RT_CALL_ENTRY(c_call);
    RT_CALL_ENTRY(c_define);
    RT_CALL_ENTRY(c_delete_frame);
    RT_CALL_ENTRY(c_draw_line);
    RT_CALL_ENTRY(c_exec_bind);
    RT_CALL_ENTRY(c_include);
    RT_CALL_ENTRY(c_invalid_cmd);
    RT_CALL_ENTRY(c_no_reinclude);
    RT_CALL_ENTRY(c_release_frame);
    RT_CALL_ENTRY(c_select_frame);
    RT_CALL_ENTRY(c_set_color);
    RT_CALL_ENTRY(c_set_position);
    RT_CALL_ENTRY(c_set_rotation);
    RT_CALL_ENTRY(c_set_scale);
    RT_CALL_ENTRY(c_set_transform);
    RT_CALL_ENTRY(c_undefine);

    const std::unordered_map<cmd_type, runtime_call_t> call_map = 
    {
        { cmd_type::CALL,           &c_call },
        { cmd_type::DEFINE,         &c_define },
        { cmd_type::DELETE_FRAME,   &c_delete_frame },
        { cmd_type::DRAW_LINE,      &c_draw_line },
        { cmd_type::EXEC_BIND,      &c_exec_bind},
        { cmd_type::INCLUDE,        &c_include},
        { cmd_type::INVALID_CMD,    &c_invalid_cmd},
        { cmd_type::NO_REINCLUDE,   &c_no_reinclude},
        { cmd_type::RELEASE_FRAME,  &c_release_frame},
        { cmd_type::SELECT_FRAME,   &c_select_frame},
        { cmd_type::SET_COLOR,      &c_set_color},
        { cmd_type::SET_POSITION,   &c_set_position},
        { cmd_type::SET_ROTATION,   &c_set_rotation},
        { cmd_type::SET_SCALE,      &c_set_scale},
        { cmd_type::SET_TRANSFORM,  &c_set_transform},
        { cmd_type::UNDEFINE,       &c_undefine}
    };

    RT_CALL_ENTRY(c_call)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        std::vector<parsed_stmt>& instructions = 
            c_inst.data.definitions[defname];

        for(auto& inst : instructions)
        {
            auto& call = call_map.at(inst.cmd);
            call(c_inst, inst.args);
        }
    }

    RT_CALL_ENTRY(c_define)
    { 
        expect_argc(args, 2);
        const std::string& defname = args[0];
        const std::string& defbody = args[1];

        std::stringstream ssbody(defbody);
        reader rdr(ssbody);
        auto parsed_def = rdr.process();
        c_inst.data.definitions.emplace(defname, parsed_def);
    }

    RT_CALL_ENTRY(c_delete_frame)
    {
        expect_argc(args, 1);
        const std::string& framename = args[0];
        c_inst.context.delete_frame(framename);
    }

    RT_CALL_ENTRY(c_draw_line)
    {
        expect_argc(args, 4);
        float sx = std::stof(args[0]);
        float sy = std::stof(args[1]);
        float ex = std::stof(args[2]);
        float ey = std::stof(args[3]);
        vector2 from(sx, sy);
        vector2 to(ex, ey);
        c_inst.context.draw_line(from, to);
    }

    RT_CALL_ENTRY(c_exec_bind)
    {
        expect_argc(args, 1);
        const std::string& bname = args[0];
        std::vector<std::string> oargs;
        if(args.size() > 1)
        {
            std::copy(args.begin() + 1, args.end(), std::back_inserter(oargs));
        }
        c_inst.data.bindings[bname](c_inst, oargs);
    }

    RT_CALL_ENTRY(c_include)
    {
        expect_argc(args, 1);
        const std::string& name = args[0];

        if(c_inst.data.include_once_ids.count(name) > 0)
        {
            return;
        }
        runtime* rptr = c_inst.runtime_ptr();
        std::vector<parsed_stmt> instructions;
        if(rptr->is_include_cached(name))
        {
            instructions = rptr->get_cached_include(name);
        }
        else
        {
            const std::string& ipath = rptr->get_include_path(name);
            std::ifstream ifs(ipath);
            reader rdr(ifs);
            instructions = rdr.process();
            rptr->cache_parsed_include(name, instructions);
        }

        for(auto& stmt : instructions)
        {
            auto& rtcall = call_map.at(stmt.cmd);
            rtcall(c_inst, stmt.args);
        }
    }

    RT_CALL_ENTRY(c_invalid_cmd)
    { 
        throw std::invalid_argument("Attempt to execute invalid command!");
    }

    RT_CALL_ENTRY(c_no_reinclude)
    { 
        c_inst.mark_include_once();
    }

    RT_CALL_ENTRY(c_release_frame)
    { 
        c_inst.context.release_frame();
    }

    RT_CALL_ENTRY(c_select_frame)
    { 
        expect_argc(args, 1);
        const std::string& framename = args[0];
        c_inst.context.select_frame(framename);
    }

    RT_CALL_ENTRY(c_set_color)
    { 
        expect_argc(args, 3);
        uint8_t r = std::min(std::stoi(args[0]), 255);
        uint8_t g = std::min(std::stoi(args[1]), 255);
        uint8_t b = std::min(std::stoi(args[2]), 255);
        uint8_t a = 255;
        if(args.size() > 3)
        {
            a = std::min(std::stoi(args[3]), 255);
        }

        color_rgba color(r, g, b, a);
        c_inst.context.set_color(color);
    }

    RT_CALL_ENTRY(c_set_position)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_position(vector2(x, y));
    }

    RT_CALL_ENTRY(c_set_rotation)
    { 
        expect_argc(args, 1);
        float rotation = std::stof(args[0]);
        c_inst.context.set_rotation(rotation);
    }

    RT_CALL_ENTRY(c_set_scale)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_scale(vector2(x, y));
    }

    RT_CALL_ENTRY(c_set_transform)
    { 
        expect_argc(args, 5);
        float px = std::stof(args[0]);
        float py = std::stof(args[1]);
        float sx = std::stof(args[2]);
        float sy = std::stof(args[3]);
        float ra = std::stof(args[4]);
        transform2 tform(vector2(px, py), vector2(sx, sy), ra);
        c_inst.context.set_transform(std::move(tform));
    }

    RT_CALL_ENTRY(c_undefine)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        c_inst.data.definitions.erase(defname);
    }
}