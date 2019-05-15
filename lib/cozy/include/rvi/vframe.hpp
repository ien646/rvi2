#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <vector>

#include <rvi/line_container.hpp>

namespace rvi
{
    struct vframe
    {
        GLuint vao = 0u;
        GLuint vbo_pos = 0u;
        GLuint vbo_col = 0u;
        line_container line_data;

        vframe() = delete;
        vframe(line_container&& line_data);
        
        vframe(const vframe& cp_src) = delete;

        vframe(vframe&& mv_src) noexcept;

        void destroy();
    };
}