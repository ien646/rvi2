#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>

#include <runtime.hpp>

#include "shader_utils.hpp"

namespace rvi
{
    struct vframe
    {
        GLuint vao;
        GLuint vbo;
        std::vector<float> line_data;
    };

    class opengl_ctx
    {
    private:
        GLuint _shader_program;
        std::unordered_map<std::string, vframe> _vframes;
        runtime* _runtime_ptr;
        int _client_id;
        size_t _line_count = 0;

    public:
        opengl_ctx(runtime* rptr, int client_id);
        void refresh();
        void draw();
    
    private:
        void create_frame_obj(const std::string& name, std::vector<line>&& lines);
    };
}