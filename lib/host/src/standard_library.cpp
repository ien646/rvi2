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

    void stitch_fill_h(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_STITCH_FILL_H");

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

    void stitch_fill_v(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_STITCH_FILL_H");

        std::vector<vector2> points;
        bool top = false;
        float y = 0.0F;
        for(; y <= 1.0F; y += step_sz)
        {
            points.push_back(vector2((top ? 1.0F : 0.0F), y));
            top = !top;
        }

        if(y > 1.0F)
        {
            float q = step_sz - (1.0F - y);
            if(top)
            {
                q = 1 - q;
            }
            points.push_back(vector2(q, 1.0F));
        }

        auto current_it = points.begin();

        for(auto it = points.begin() + 1; it != points.end(); ++it)
        {
            ctx.draw_line(*current_it, *it);
            current_it = it;
        }
        ctx.release_frame();
    }

    void parallel_fill_h(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_PARALLEL_FILL_H");
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

    void parallel_fill_v(client_context& ctx, float step_sz)
    {
        ctx.select_frame("__STD_PARALLEL_FILL_V");
        float x_accum = step_sz;
        while(x_accum <= 1.00F)
        {
            ctx.draw_line(vector2(x_accum, 0.0F), vector2(x_accum, 1.0F));
            x_accum += step_sz;
        }
        ctx.release_frame();
    }

    vector2 get_distort_point_offset(
        vector2 point, 
        vector2 ul, 
        vector2 ur, 
        vector2 ll, 
        vector2 lr)
    {
        float offset_x = 0.0F;
        float offset_y = 0.0F;

        // ul
        float ul_f_sample = point.y * (1 - point.x);
        offset_x += ul.x * ul_f_sample;
        offset_y += ul.y * ul_f_sample;

        // ur
        float ur_f_sample = point.y * point.x;
        offset_x += ur.x * ur_f_sample;
        offset_y += ur.y * ur_f_sample;

        // ll
        float ll_f_sample = (1 - point.y) * (1 - point.x);
        offset_x += ll.x * ll_f_sample;
        offset_y += ll.y * ll_f_sample;

        // lr
        float lr_f_sample = (1 - point.y) * point.x;
        offset_x += lr.x * lr_f_sample;
        offset_y += lr.y * lr_f_sample;

        return vector2(offset_x, offset_y);
    }

    void distort(frame* fptr, vector2 ul, vector2 ur, vector2 ll, vector2 lr)
    {
        auto& lines = fptr->lines();
        for(auto it = lines.position_begin(); it != lines.position_end(); it += 2)
        {
            float& x = *it;
            float& y = *(it + 1);

            vector2 offset = get_distort_point_offset(vector2(x, y), ul, ur, ll, lr);

            x += offset.x;
            y += offset.y;
        }
    }    

    void distort_recursive(frame* fptr, vector2 ul, vector2 ur, vector2 ll, vector2 lr)
    {
        distort(fptr, ul, ur, ll, lr);

        std::vector<frame*> pending_children;
        std::transform(
            fptr->children().begin(), 
            fptr->children().end(), 
            std::back_inserter(pending_children), 
            [&](auto& uptr) { return uptr.get(); });

        while(!pending_children.empty())
        {
            frame* child = pending_children.back();
            pending_children.pop_back();

            std::transform(
                child->children().begin(), 
                child->children().end(), 
                std::back_inserter(pending_children), 
                [&](auto& uptr) { return uptr.get(); });
            
            vector2 child_offset = get_distort_point_offset(
                child->transform().position,
                ul, ur, ll, lr
            );

            child->set_position(child->transform().position + child_offset);
            distort(child, ul, ur, ll, lr);
        }
    }
}