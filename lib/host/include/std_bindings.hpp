#pragma once

#include "client_instance.hpp"

namespace rvi::std_bindings
{
    static const float DEF_FONT_SZ = 0.03F;
    static const float DEF_FONT_HSEP = 0.075F;
    static const float DEF_FONT_MARGIN = 0.01F;
    static const char  DEF_FONT_WRAP_SEP_CH = ' ';

    extern void print(client_instance& c_inst, const arglist_t& args);
    extern void printw(client_instance& c_inst, const arglist_t& args);
    extern void print_ex(client_instance& c_inst, const arglist_t& args);
    extern void printw_ex(client_instance& c_inst, const arglist_t& args);
    extern void printc(client_instance& c_inst, const arglist_t& args);
    extern void printcw(client_instance& c_inst, const arglist_t& args);
    
    extern void _print(
        client_instance& c_inst,
        const std::string& calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v);

    extern void _printw(
        client_instance& c_inst,
        const std::string& calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v,
        char wsep_char);

    extern void box_border(client_instance& c_inst, const arglist_t& args);

    extern void init_std_bindings(client_instance& c_inst);
}