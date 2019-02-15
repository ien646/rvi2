#pragma once

#include <string>
#include <rvi/client_instance.hpp>

namespace rvi::standard
{
    extern vector2  DEFAULT_FONT_SZ;
    extern vector2  DEFAULT_FONT_SEP;
    extern vector2  DEFAULT_FONT_MARGIN;
    extern char     DEFAULT_WRAP_SEP_CHAR;
    extern float    DEFAULT_WRAP_LNSEP_V;

    struct print_settings
    {
        vector2 font_size   = DEFAULT_FONT_SZ;
        vector2 font_sep    = DEFAULT_FONT_SEP;
        vector2 font_margin = DEFAULT_FONT_MARGIN;
        char wrap_sep_char  = DEFAULT_WRAP_SEP_CHAR;
        float wrap_vsep     = DEFAULT_WRAP_LNSEP_V;
    };

    extern void print(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        const print_settings& p_set = print_settings()
    );

    extern void printw(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        const print_settings& p_set = print_settings()
    );

    extern void box_border(
        client_context& ctx
    );

    extern void grid_fill(
        client_context& ctx, 
        float x_step, 
        float y_step
    );

    extern void stitch_fill(
        client_context& ctx, 
        float step_sz
    );  

    extern void horizontal_fill(
        client_context& ctx, 
        float step_sz
    );

    extern void vertical_fill(
        client_context& ctx, 
        float step_sz
    );
}