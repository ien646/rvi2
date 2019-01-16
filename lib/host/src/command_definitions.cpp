#include <rvi/command_definitions.hpp>

#include <fstream>
#include <utility>

#include <rvi/client_instance.hpp>
#include <rvi/runtime.hpp>
#include <rvi/assert.hpp>
#include <rvi/reader.hpp>
#include <rvi/parsed_stmt.hpp>

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

    const std::unordered_map<command_type, runtime_cmd_t> command_definitions = 
    {
        { command_type::MACRO,          &command_impl::macro },
        { command_type::DEFINE,         &command_impl::define },
        { command_type::DELETE_FRAME,   &command_impl::delete_frame },
        { command_type::DRAW_LINE,      &command_impl::draw_line },
        { command_type::CALL,           &command_impl::call},
        { command_type::INCLUDE,        &command_impl::include},
        { command_type::INVALID_CMD,    &command_impl::invalid_cmd},
        { command_type::NO_REINCLUDE,   &command_impl::no_reinclude},
        { command_type::RELEASE_FRAME,  &command_impl::release_frame},
        { command_type::SELECT_FRAME,   &command_impl::select_frame},
        { command_type::SET_COLOR,      &command_impl::set_color},
        { command_type::SET_POSITION,   &command_impl::set_position},
        { command_type::SET_ROTATION,   &command_impl::set_rotation},
        { command_type::SET_SCALE,      &command_impl::set_scale},
        { command_type::SET_TRANSFORM,  &command_impl::set_transform},
        { command_type::UNDEFINE,       &command_impl::undefine},
        { command_type::SET_CLICKABLE,  &command_impl::set_clickable},
        { command_type::UNSET_CLICKABLE,&command_impl::unset_clickable}
    };

    RVI_RT_CMD_ENTRY(command_impl::macro)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        std::vector<parsed_stmt>& instructions = 
            c_inst.data.macros[defname];

        for(auto& inst : instructions)
        {
            auto& cmd = command_definitions.at(inst.cmd);
            cmd(c_inst, inst.args);
        }
    }

    RVI_RT_CMD_ENTRY(command_impl::define)
    { 
        expect_argc(args, 2);
        const std::string& defname = args[0];
        const std::string& defbody = args[1];

        std::stringstream ssbody(defbody);
        reader rdr(ssbody);
        auto parsed_def = rdr.process();
        c_inst.data.macros.emplace(defname, parsed_def);
    }

    RVI_RT_CMD_ENTRY(command_impl::delete_frame)
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

    RVI_RT_CMD_ENTRY(command_impl::draw_line)
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

    RVI_RT_CMD_ENTRY(command_impl::call)
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

    RVI_RT_CMD_ENTRY(command_impl::include)
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
            auto& cmd = command_definitions.at(stmt.cmd);
            cmd(c_inst, stmt.args);
        }
        c_inst.pop_include();
    }

    RVI_RT_CMD_ENTRY(command_impl::invalid_cmd)
    {
        throw std::invalid_argument("Attempt to execute invalid command!");
    }

    RVI_RT_CMD_ENTRY(command_impl::no_reinclude)
    { 
        c_inst.mark_include_once();
    }

    RVI_RT_CMD_ENTRY(command_impl::release_frame)
    { 
        c_inst.context.release_frame();
    }

    RVI_RT_CMD_ENTRY(command_impl::select_frame)
    { 
        expect_argc(args, 1);
        const std::string& framename = args[0];
        c_inst.context.select_frame(framename);
    }

    RVI_RT_CMD_ENTRY(command_impl::set_color)
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

    RVI_RT_CMD_ENTRY(command_impl::set_position)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_position(vector2(x, y));
    }

    RVI_RT_CMD_ENTRY(command_impl::set_rotation)
    { 
        expect_argc(args, 1);
        float rotation = std::stof(args[0]);
        c_inst.context.set_rotation(rotation);
    }

    RVI_RT_CMD_ENTRY(command_impl::set_scale)
    { 
        expect_argc(args, 2);
        float x = std::stof(args[0]);
        float y = std::stof(args[1]);
        c_inst.context.set_scale(vector2(x, y));
    }

    RVI_RT_CMD_ENTRY(command_impl::set_transform)
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

    RVI_RT_CMD_ENTRY(command_impl::undefine)
    {
        expect_argc(args, 1);
        const std::string& defname = args[0];
        c_inst.data.macros.erase(defname);
    }

    RVI_RT_CMD_ENTRY(command_impl::set_clickable)
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

    RVI_RT_CMD_ENTRY(command_impl::unset_clickable)
    {
        // expect_argc(args, 0);
        frame* fptr = c_inst.context.selected_frame();
        c_inst.unset_clickable_frame(fptr);
    }
}