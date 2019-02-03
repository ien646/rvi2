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
        float font_sz_h = DEFAULT_FONT_SZ_H,
        float font_sz_v = DEFAULT_FONT_SZ_V,
        float font_sep_h = DEFAULT_FONT_SEP_H,
        float font_sep_v = DEFAULT_FONT_SEP_V,
        float font_margin_h = DEFAULT_FONT_MARGIN_H,
        float font_margin_v = DEFAULT_FONT_MARGIN_V
    );

    extern void printw(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        float font_sz_h = DEFAULT_FONT_SZ_H,
        float font_sz_v = DEFAULT_FONT_SZ_V,
        float font_sep_h = DEFAULT_FONT_SEP_H,
        float font_sep_v = DEFAULT_FONT_SEP_V,
        float font_margin_h = DEFAULT_FONT_MARGIN_H,
        float font_margin_v = DEFAULT_FONT_MARGIN_V,
        char wrap_sep_char = DEFAULT_WRAP_SEP_CHAR,
        float wrap_vsep = DEFAULT_WRAP_LNSEP_V
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
}