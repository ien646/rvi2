#include "opengl_ctx.hpp"

#define SCFLOAT(f) static_cast<float>(f)

namespace rvi
{
    int opengl_ctx::_client_id;
    runtime* opengl_ctx::_runtime_ptr;
    vector2 opengl_ctx::_cursor_pos;

    opengl_ctx::opengl_ctx(runtime* rptr, int cid)
    {
        _runtime_ptr = rptr;
        _client_id = cid;
        init_default_shaders(&_shader_program);
        glLineWidth(1);
    }

    void opengl_ctx::refresh()
    {
        auto snapshot = _runtime_ptr->snapshot_diff_relative(_client_id);
        for(auto&& frame_entry : snapshot)
        {
            if(frame_entry.deleted)
            {
                _vframes.erase(frame_entry.name);
            }
            else if (frame_entry.lines.size() > 0)
            {
                auto& entry = vframe_from_snapshot_entry(frame_entry);
                setup_vframe_ogl(entry);
            }
        }
    }

    const vframe& opengl_ctx::vframe_from_snapshot_entry(relative_snapshot_entry& entry)
    {
        vframe vf;
        glGenVertexArrays(1, &vf.vao);
        glGenBuffers(1, &vf.vbo);
        for(auto& line : entry.lines)
        {
            vf.line_data.push_back(line.start.position.x);
            vf.line_data.push_back(line.start.position.y);
            vf.line_data.push_back(SCFLOAT(line.start.color.rgba()));
            vf.line_data.push_back(line.end.position.x);
            vf.line_data.push_back(line.end.position.y);
            vf.line_data.push_back(SCFLOAT(line.end.color.rgba()));
        }
        _vframes.emplace(entry.name, std::move(vf));
        return _vframes[entry.name];
    }

    void opengl_ctx::setup_vframe_ogl(const vframe& vf)
    {
        // Bind vao/vbo
        glBindVertexArray(vf.vao);
        glBindBuffer(GL_ARRAY_BUFFER, vf.vbo);

        // Bind data to vbo
        glBufferData(
            GL_ARRAY_BUFFER, 
            vf.line_data.size() * sizeof(float),
            vf.line_data.data(),
            GL_DYNAMIC_DRAW
        );

        // Setup shader inputs
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);

        // Unbind vao/vbo
        glBindBuffer(GL_ARRAY_BUFFER, NULL);
        glBindVertexArray(NULL);
    }

    void opengl_ctx::draw(float delta_time)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glUseProgram(_shader_program);
        GLint uloc = glGetUniformLocation(_shader_program, "delta_time");
        if(uloc >= 0)
        {
            glUniform1f(uloc, delta_time);
        }
        
        for(auto &vfp : _vframes)
        {
            glBindVertexArray(vfp.second.vao);
            glDrawArrays(GL_LINES, 0, vfp.second.line_data.size() * sizeof(line));
            glBindVertexArray(NULL);
        }
    }

    void opengl_ctx::setup_mouse_callbacks(GLFWwindow* wnd)
    {
        glfwSetMouseButtonCallback(wnd, &mouse_press_callback);
        glfwSetCursorPosCallback(wnd, &mouse_pos_callback);
    }

    void opengl_ctx::mouse_pos_callback(GLFWwindow* wnd, double px, double py)
    {
        float fpx = static_cast<float>(px);
        float fpy = static_cast<float>(py);

        int w, h;
        glfwGetWindowSize(wnd, &w, &h);

        float x = fpx / w;
        float y = 1 - (fpy / h);
        _cursor_pos = rvi::vector2(x, y);
    }

    void opengl_ctx::mouse_press_callback(GLFWwindow* /**/, int key, int act, int /**/)
    {
        if(key == GLFW_MOUSE_BUTTON_LEFT && act == GLFW_PRESS)
        {
            auto& inst = _runtime_ptr->get_instance(_client_id);
            inst.user_click(_cursor_pos);
        }
    }
}