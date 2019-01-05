#include "vframe.hpp"

vframe::vframe(vframe&& mv_src) noexcept
{
    vao = mv_src.vao;
    vbo = mv_src.vbo;
    line_data = std::move(mv_src.line_data);
    mv_src._moved = true;
}

vframe::~vframe()
{
    if (!_moved)
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
    }
}