#pragma once

#include <string>
#include <rvi/client_instance.hpp>

namespace rvi::standard
{
    extern float DEFAULT_FONT_SZ_H;
    extern float DEFAULT_FONT_SZ_V;
    extern float DEFAULT_FONT_SEP_H;
    extern float DEFAULT_FONT_SEP_V;
    extern float DEFAULT_FONT_MARGIN_H;
    extern float DEFAULT_FONT_MARGIN_V;
    extern char  DEFAULT_WRAP_SEP_CHAR;
    extern float DEFAULT_WRAP_LNSEP_V;

    extern void print(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        float font_sz_h = 0.05F,
        float font_sz_v = 0.05F,
        float font_sep_h = 0.01F,
        float font_sep_v = 0.0F,
        float font_margin_h = 0.0F,
        float font_margin_v = 0.0F
    );

    extern void printw(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v,
        char wrap_sep_char,
        float wrap_vsep
    );

    extern void box_border(
        client_context& ctx,
        color_rgba color
    );

    extern void grid_fill(
        client_context& ctx, 
        float x_step, 
        float y_step, 
        color_rgba color
    );

    extern void stitch_fill(
        client_context& ctx, 
        float step_sz, 
        color_rgba color
    );
}