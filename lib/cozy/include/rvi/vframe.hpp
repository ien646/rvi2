#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <vector>

namespace rvi
{
    struct vframe
    {
        GLuint vao = 0u;
        GLuint vbo = 0u;
        std::vector<float> line_data;

        vframe() = default;
        vframe(const vframe& cp_src) = delete;

        vframe(vframe&& mv_src) noexcept;

        ~vframe();

    private:
        bool _moved = false;
    };
}