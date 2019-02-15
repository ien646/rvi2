#include <rvi/standard_library.hpp>

#include <algorithm>

namespace rvi::standard
{
    vector2 DEFAULT_FONT_SZ      = vector2(0.025F, 0.025F);
    vector2 DEFAULT_FONT_SEP     = vector2(0.010F, 0.0F);
    vector2 DEFAULT_FONT_MARGIN  = vector2(0.0F, 0.0F);
    char  DEFAULT_WRAP_SEP_CHAR  = ' ';
    float DEFAULT_WRAP_LNSEP_V   = 0.020F;

    void print(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        const print_settings& p_set)
    {
        client_context* ctx = c_inst.get_context();
        frame* save_fptr = ctx->selected_frame();

        vector2 offset(p_set.font_margin.x, p_set.font_margin.y);

        ctx->select_frame(calling_frame);
        ctx->select_frame("__STD_PRINT");
        int idx = 0;
        for (auto& ch : text)
        {
            std::string defn = std::string(1, ch);
            ctx->select_frame("char_" + std::to_string(idx) + "_[" + defn + "]");
            {
                ctx->set_scale(vector2(p_set.font_size.x, p_set.font_size.y));
                ctx->set_transform_scale_abs(true);
                ctx->set_position(offset);
                c_inst.exec_macro(defn);
            }
            ctx->release_frame();

            offset += vector2(p_set.font_size.x + p_set.font_sep.x, p_set.font_sep.y);
            ++idx;
        }
        ctx->release_frame(); // "text_print"
        ctx->select_frame(save_fptr);
    }

    void printw(
        client_instance& c_inst,
        frame* calling_frame,
        const std::string& text,
        const print_settings& p_set)
    {
        client_context* ctx = c_inst.get_context();
        frame* save_fptr = ctx->selected_frame();

        float x_max_sz = calling_frame->get_absolute_transform().scale.x;
        float y_max_sz = calling_frame->get_absolute_transform().scale.y;

        vector2 offset(
            p_set.font_margin.x,
            (y_max_sz - p_set.font_size.y) - p_set.font_margin.y
        );

        bool first = true;

        ctx->select_frame(calling_frame);
        ctx->select_frame("__STD_PRINT_WRAP");
        std::stringstream tstr(text);
        std::string line;
        int idx = 0;
        while(std::getline(tstr, line, p_set.wrap_sep_char))
        {
            line += p_set.wrap_sep_char;
            if(!first)
            {
                float finalPos = offset.x + 
                    (line.size() * p_set.font_size.x) + 
                    ((line.size() - 1) * p_set.font_sep.x);

                if(finalPos > x_max_sz)
                {
                    offset.x = p_set.font_margin.x;
                    offset.y -= (p_set.font_size.y + p_set.wrap_vsep);
                }
            }
            first = false;
            for (auto& ch : line)
            {
                std::string defn = std::string(1, ch);
                
                ctx->select_frame("char_" + std::to_string(idx) + "_[" + defn + "]");
                {
                    ctx->set_scale(vector2(p_set.font_size.x, p_set.font_size.y));
                    ctx->set_transform_scale_abs(true);
                    ctx->set_position(offset);
                    c_inst.exec_macro(defn);
                }
                ctx->release_frame();

                offset += vector2(p_set.font_size.x + p_set.font_sep.x, p_set.font_sep.y);
                ++idx;
            }
        }
        ctx->release_frame();
        ctx->select_frame(save_fptr);
    }

    void box_border(client_context& ctx)
    {
        ctx.select_frame("__STD_BOX_BORDER");
        {
            ctx.draw_line(vector2(0, 0), vector2(1, 0)); //  -
            ctx.draw_line(vector2(0, 1), vector2(1, 1)); //  =
            ctx.draw_line(vector2(0, 0), vector2(0, 1)); // |=
            ctx.draw_line(vector2(1, 0), vector2(1, 1)); // |=|
        } ctx.release_frame();
    }

    void grid_fill(client_context& ctx, float x_step, float y_step)
    {
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
        } ctx.release_frame();
    }

    void stitch_fill(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_STITCH_FILL");

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
        ctx.release_frame();
    }

    void horizontal_fill(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_HORIZONTAL_FILL");
        {
            float y_accum = step_sz;
            while(y_accum <= 1.00F)
            {
                ctx.draw_line(vector2(0.0F, y_accum), vector2(1, y_accum));
                y_accum += step_sz;
            }
        }
        ctx.release_frame();
    }

    void vertical_fill(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_VERTICAL_FILL");
        float x_accum = step_sz;
        while(x_accum <= 1.00F)
        {
            ctx.draw_line(vector2(x_accum, 0.0F), vector2(x_accum, 1.0F));
            x_accum += step_sz;
        }
        ctx.release_frame();
    }
}