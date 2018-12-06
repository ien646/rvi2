#include <glad/glad.hpp> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <string_view>

#define OGL_PRINT_ERR(fname) ogl_print_errors(fname, __LINE__) 

static void ogl_print_errors(std::string_view fname, int ln_no)
{    
    GLenum err;
    std::cout << std::hex;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "OPENGL-ERROR: " << "0x" << err << std::endl
            << "  On file: " << fname << "(" << ln_no << ")" << std::endl;
    }
}