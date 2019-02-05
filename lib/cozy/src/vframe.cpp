#include <rvi/vframe.hpp>

namespace rvi
{
    vframe::vframe(vframe&& mv_src) noexcept
    {
        vao = mv_src.vao;
        vbo_pos = mv_src.vbo_pos;
        vbo_col = mv_src.vbo_col;
        line_data = std::move(mv_src.line_data);
        mv_src._moved = true;
    }

    vframe::~vframe()
    {
        if (!_moved)
        {
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo_pos);
            glDeleteBuffers(1, &vbo_col);
        }
    }
}