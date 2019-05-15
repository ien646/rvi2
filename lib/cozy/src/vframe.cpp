#include <rvi/vframe.hpp>

namespace rvi
{
    vframe::vframe(line_container&& l_data)
    {
        line_data = std::move(l_data);
    }

    vframe::vframe(vframe&& mv_src) noexcept
    {
        vao = mv_src.vao;
        vbo_pos = mv_src.vbo_pos;
        vbo_col = mv_src.vbo_col;
        line_data = std::move(mv_src.line_data);
    }

    void vframe::destroy()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo_pos);
        glDeleteBuffers(1, &vbo_col);            
    }
}