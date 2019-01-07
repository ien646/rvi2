#include <rvi/window.hpp>

#include <iostream>

namespace rvi
{
    static void resize_callback(GLFWwindow* /**/, int w, int h)
    {
        glViewport(0, 0, w, h);
    }

    window::window(uint32_t sz_x, uint32_t sz_y, const std::string& title)
    {
        glfwInit();    
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        _wndptr = glfwCreateWindow(sz_x, sz_y, title.c_str(), NULL, NULL);

        if (_wndptr == NULL) 
        {
            std::cout << "GLFW Window creation failure!" << std::endl;
            glfwTerminate();
            std::exit(-1);
        }

        glfwMakeContextCurrent(_wndptr);
        glfwSetFramebufferSizeCallback(_wndptr, &resize_callback);

        int glad_ld_res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if(!glad_ld_res)
        {
            std::cout << "GLAD loading failure!" << std::endl;
            glfwTerminate();
            std::exit(-1);
        }
    }

    bool window::should_close()
    {
        return glfwWindowShouldClose(_wndptr);
    }

    GLFWwindow* window::wnd_ptr()
    {
        return _wndptr;
    }
}