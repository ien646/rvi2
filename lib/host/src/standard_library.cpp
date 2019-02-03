#include <rvi/standard_library.hpp>

#include <algorithm>

namespace rvi::standard
{
    float DEFAULT_FONT_SZ_H      = 0.04F;
    float DEFAULT_FONT_SZ_V      = 0.04F;
    float DEFAULT_FONT_SEP_H     = 0.01F;
    float DEFAULT_FONT_SEP_V     = 0.00F;
    float DEFAULT_FONT_MARGIN_H  = 0.00F;
    float DEFAULT_FONT_MARGIN_V  = 0.00F;
    char  DEFAULT_WRAP_SEP_CHAR  = ' ';
    float DEFAULT_WRAP_LNSEP_V   = 0.02F;

    void print(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        float font_sz_h,
        float font_sz_v,
        float font_sep_h,
        float font_sep_v,
        float font_margin_h,
        float font_margin_v)
    {
        client_context* ctx = c_inst.get_context();
        frame* save_fptr = ctx->selected_frame();

        vector2 offset(font_margin_h, font_margin_v);

        ctx->select_frame(calling_frame);
        int idx = 0;
        for (auto& ch : text)
        {
            std::string defn = std::string(1, ch);
            ctx->select_frame("char_" + std::to_string(idx) + "_[" + defn + "]");
            {
                ctx->set_scale(vector2(font_sz_h, font_sz_v));
                ctx->set_transform_scale_abs(true);
                ctx->set_position(offset);
                c_inst.exec_macro(defn);
            }
            ctx->release_frame();

            offset += vector2(font_sz_h + font_sep_h, font_sep_v);
            ++idx;
        }
        ctx->select_frame(save_fptr);
    }

    void printw(
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
        float wrap_vsep)
    {
        client_context* ctx = c_inst.get_context();
        frame* save_fptr = ctx->selected_frame();

        float x_max_sz = calling_frame->get_absolute_transform().scale.x;
        float y_max_sz = calling_frame->get_absolute_transform().scale.y;

        vector2 offset(
            font_margin_h,
            (y_max_sz - font_sz_v) - font_margin_v
        );

        bool first = true;

        ctx->select_frame(calling_frame);
        std::stringstream tstr(text);
        std::string line;
        int idx = 0;
        while(std::getline(tstr, line, wrap_sep_char))
        {
            line += wrap_sep_char;
            if(!first)
            {
                float finalPos = offset.x + 
                    (line.size() * font_sz_h) + 
                    ((line.size() - 1) * font_sep_h);

                if(finalPos > x_max_sz)
                {
                    offset.x = font_margin_h;
                    offset.y -= (font_sz_v + wrap_vsep);
                }
            }
            first = false;
            for (auto& ch : line)
            {
                std::string defn = std::string(1, ch);
                
                ctx->select_frame("char_" + std::to_string(idx) + "_[" + defn + "]");
                {
                    ctx->set_scale(vector2(font_sz_h, font_sz_v));
                    ctx->set_transform_scale_abs(true);
                    ctx->set_position(offset);
                    c_inst.exec_macro(defn);
                }
                ctx->release_frame();

                offset += vector2(font_sz_h + font_sep_h, font_sep_v);
                ++idx;
            }
        }
        ctx->select_frame(save_fptr);
    }

    void box_border(client_context& ctx, color_rgba color)
    {
        color_rgba save_color = ctx.current_color();
        ctx.select_frame("__STD_BOX_BORDER");
        {
            ctx.set_color(color);
            ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
            ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
            ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
            ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        }
        ctx.set_color(save_color);
    }

    void grid_fill(client_context& ctx, float x_step, float y_step, color_rgba color)
    {
        color_rgba save_color = ctx.current_color();

        ctx.set_color(color);
        ctx.select_frame("__STD_GRID_FILL");
        {            
            for(float x = x_step; x < 1.0F; x += x_step)
            {
                ctx.draw_line(vector2(x, 0), vector2(x, 1));
            }

            for(float y = y_step; y < 1.0F; y += y_step)
            {
                ctx.draw_line(vector2(0, y), vector2(1, y));
            }
        }
        ctx.set_color(save_color);
    }

    void stitch_fill(client_context& ctx, float step_sz, color_rgba color)
    {
        color_rgba save_color = ctx.current_color();

        ctx.select_frame("__STD_STITCH_FILL");
        ctx.set_color(color);

        std::vector<vector2> points;
        bool top = false;
        float x = 0.0F;
        for(; x <= 1.0F; x += step_sz)
        {
            points.push_back(vector2(x, (top ? 1.0F : 0.0F)));
            top = !top;
        }

        if(x > 1.0F)
        {
            float q = step_sz - (1.0F - x);
            if(top)
            {
                q = 1 - q;
            }
            points.push_back(vector2(1.0F, q));
        }

        auto current_it = points.begin();

        for(auto it = points.begin() + 1; it != points.end(); ++it)
        {
            ctx.draw_line(*current_it, *it);
            current_it = it;
        }

        ctx.set_color(save_color);
    }
}