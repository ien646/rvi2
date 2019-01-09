#include <rvi/cmd_def_map.hpp>

#include <fstream>
#include <utility>

#include <rvi/client_instance.hpp>
#include <rvi/runtime.hpp>
#include <rvi/assert.hpp>
#include <rvi/reader.hpp>
#include <rvi/parsed_stmt.hpp>

#define RT_CMD_ENTRY(name) \
    void name( \
        [[maybe_unused]] client_instance& c_inst, \
        [[maybe_unused]] const arglist_t& args)

#define STR(v) std::to_string(v)

namespace rvi
{
    // -- HELPER METHODS --
    void expect_argc(const arglist_t& args, size_t count)
    {
        r_assert(
            args.size() >= count,
            "Expected argument count of " 
                + STR(count) 
                + "; Actual arg count: " 
                + STR(args.size())
        );
    }
    // --------------------

    // -- FWD DECLARE --
    RT_CMD_ENTRY(c_macro);
    RT_CMD_ENTRY(c_define);
    RT_CMD_ENTRY(c_delete_frame);
    RT_CMD_ENTRY(c_draw_line);
    RT_CMD_ENTRY(c_call);
    RT_CMD_ENTRY(c_include);
    RT_CMD_ENTRY(c_invalid_cmd);
    RT_CMD_ENTRY(c_no_reinclude);
    RT_CMD_ENTRY(c_release_frame);
    RT_CMD_ENTRY(c_select_frame);
    RT_CMD_ENTRY(c_set_color);
    RT_CMD_ENTRY(c_set_position);
    RT_CMD_ENTRY(c_set_rotation);
    RT_CMD_ENTRY(c_set_scale);
    RT_CMD_ENTRY(c_set_transform);
    RT_CMD_ENTRY(c_undefine);
    RT_CMD_ENTRY(c_set_clickable);
    RT_CMD_ENTRY(c_unset_clickable);

    const std::unordered_map<cmd_type, runtime_cmd_t> cmd_def_map = 
    {
        { cmd_type::MACRO,          &c_macro },
        { cmd_type::DEFINE,         &c_define },
        { cmd_type::DELETE_FRAME,   &c_delete_frame },
        { cmd_type::DRAW_LINE,      &c_draw_line },
        { cmd_type::CALL,           &c_call},
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
        { cmd_type::UNDEFINE,       &c_undefine},
        { cmd_type::SET_CLICKABLE,  &c_set_clickable},
        { cmd_type::UNSET_CLICKABLE,&c_unset_clickable}
    };

    RT_CMD_ENTRY(c_macro)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        std::vector<parsed_stmt>& instructions = 
            c_inst.data.macros[defname];

        for(auto& inst : instructions)
        {
            auto& cmd = cmd_def_map.at(inst.cmd);
            cmd(c_inst, inst.args);
        }
    }

    RT_CMD_ENTRY(c_define)
    { 
        expect_argc(args, 2);
        const std::string& defname = args[0];
        const std::string& defbody = args[1];

        std::stringstream ssbody(defbody);
        reader rdr(ssbody);
        auto parsed_def = rdr.process();
        c_inst.data.macros.emplace(defname, parsed_def);
    }

    RT_CMD_ENTRY(c_delete_frame)
    {
        // expect_argc(args, 0);
        frame* sfptr = c_inst.context.selected_frame();

        if(args.size() > 0)
        {
            const std::string& framename = args[0];
            frame* cfptr = sfptr->get_child(framename);
            c_inst.context.delete_frame(framename);
            c_inst.unset_clickable_frame(cfptr);
        }
        else if(sfptr->has_parent())
        {
            c_inst.context.release_frame();
            c_inst.context.delete_frame(sfptr->name());
            c_inst.unset_clickable_frame(sfptr);
        }
    }

    RT_CMD_ENTRY(c_draw_line)
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

    RT_CMD_ENTRY(c_call)
    {
        expect_argc(args, 1);
        const std::string& bname = args[0];
        std::vector<std::string> oargs;
        if(args.size() > 1)
        {
            std::copy(args.begin() + 1, args.end(), std::back_inserter(oargs));
        }
        if(c_inst.data.bindings.count(bname) > 0)
        {
            c_inst.exec_binding(bname, oargs);
        }
        else
        {
            std::cerr   << "Attempt to execute non-present binding ["
                        << bname
                        << "]"
                        << std::endl;
        }
    }

    RT_CMD_ENTRY(c_include)
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

        c_inst.push_include(name);
        for(auto& stmt : instructions)
        {
            auto& cmd = cmd_def_map.at(stmt.cmd);
            cmd(c_inst, stmt.args);
        }
        c_inst.pop_include();
    }

    RT_CMD_ENTRY(c_invalid_cmd)
    {
        throw std::invalid_argument("Attempt to execute invalid command!");
    }

    RT_CMD_ENTRY(c_no_reinclude)
    { 
        c_inst.mark_include_once();
    }

    RT_CMD_ENTRY(c_release_frame)
    { 
        c_inst.context.release_frame();
    }

    RT_CMD_ENTRY(c_select_frame)
    { 
        expect_argc(args, 1);
        const std::string& framename = args[0];
        c_inst.context.select_frame(framename);
    }

    RT_CMD_ENTRY(c_set_color)
    {
        expect_argc(args, 3);
        uint8_t r = static_cast<uint8_t>(std::min(std::stoi(args[0]), 255));
        uint8_t g = static_cast<uint8_t>(std::min(std::stoi(args[1]), 255));
        uint8_t b = static_cast<uint8_t>(std::min(std::stoi(args[2]), 255));
        uint8_t a = 255;
        if(args.size() > 3)
        {
            a = static_cast<uint8_t>(std::min(std::stoi(args[3]), 255));
        }

        color_rgba color(r, g, b, a);
        c_inst.context.set_color(color);
    }

    RT_CMD_ENTRY(c_set_position)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_position(vector2(x, y));
    }

    RT_CMD_ENTRY(c_set_rotation)
    { 
        expect_argc(args, 1);
        float rotation = std::stof(args[0]);
        c_inst.context.set_rotation(rotation);
    }

    RT_CMD_ENTRY(c_set_scale)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_scale(vector2(x, y));
    }

    RT_CMD_ENTRY(c_set_transform)
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

    RT_CMD_ENTRY(c_undefine)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        c_inst.data.macros.erase(defname);
    }

    RT_CMD_ENTRY(c_set_clickable)
    {
        expect_argc(args, 1);

        std::string binding_name = args[0];
        
        float depth = 0.0F;
        if(args.size() > 1) // optional depth
        {
            depth = std::stof(args[1]);
        }

        std::vector<std::string> binding_args;
        if(args.size() > 2) // optional args
        {
            std::copy(args.begin() + 2, args.end(), std::back_inserter(binding_args));
        }

        frame* fptr = c_inst.context.selected_frame();
        c_inst.set_clickable_frame(fptr, binding_name, depth, binding_args);
    }

    RT_CMD_ENTRY(c_unset_clickable)
    {
        // expect_argc(args, 0);
        frame* fptr = c_inst.context.selected_frame();
        c_inst.unset_clickable_frame(fptr);
    }
}