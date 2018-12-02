#pragma once

#include <glad/glad.hpp>
#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>

#include <runtime.hpp>

#include "shader_utils.hpp"
#include "vframe.hpp"

namespace rvi
{
    class opengl_ctx
    {
    private:
        GLuint _shader_program;
        std::unordered_map<std::string, vframe> _vframes;        
        
        size_t _line_count = 0;

        static int _client_id;
        static runtime* _runtime_ptr;
        static vector2 _cursor_pos;

    public:
        opengl_ctx(runtime* rptr, int client_id);
        void refresh();
        void draw(float delta_time);
        
        static void setup_mouse_callbacks(GLFWwindow* wnd);
    private:        
        static void mouse_pos_callback(GLFWwindow* wnd, double px, double py);
        static void mouse_press_callback(GLFWwindow* wnd, int key, int act, int mods);
        void create_frame_obj(const std::string& name, std::vector<line>&& lines);
    };
}