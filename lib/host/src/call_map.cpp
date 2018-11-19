#include "call_map.hpp"

#include <rvi_assert.hpp>

#define RT_CALL_ENTRY(name) \
    void name(client_instance& client_inst, const arglist_t& args)

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
        
    }

    RT_CALL_ENTRY(c_define)
    { 

    }

    RT_CALL_ENTRY(c_delete_frame)
    {

    }

    RT_CALL_ENTRY(c_draw_line)
    { 

    }

    RT_CALL_ENTRY(c_exec_bind)
    {

    }

    RT_CALL_ENTRY(c_include)
    { 

    }

    RT_CALL_ENTRY(c_invalid_cmd)
    { 

    }

    RT_CALL_ENTRY(c_no_reinclude)
    { 

    }

    RT_CALL_ENTRY(c_release_frame)
    { 

    }

    RT_CALL_ENTRY(c_select_frame)
    { 

    }
    RT_CALL_ENTRY(c_set_color)
    { 

    }

    RT_CALL_ENTRY(c_set_position)
    { 

    }

    RT_CALL_ENTRY(c_set_rotation)
    { 

    }

    RT_CALL_ENTRY(c_set_scale)
    { 

    }

    RT_CALL_ENTRY(c_set_transform)
    { 

    }

    RT_CALL_ENTRY(c_undefine)
    { 

    }
}