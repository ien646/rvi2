#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class window
{
private:
    GLFWwindow* _wndptr;
public:
    window(uint32_t sz_x, uint32_t sz_y, const std::string& title);
    bool should_close();
    GLFWwindow* wnd_ptr();
};