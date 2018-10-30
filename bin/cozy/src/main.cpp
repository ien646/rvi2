#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include "window.hpp"
#include "shader_utils.hpp"

int main()
{
    window wnd(800, 600, "COZY");

    float vertex_col[] = 
    {
        0.0F, 0.0F, 1.0F, 1.0F,
        0.0F, 0.0F, 0.9F, 1.0F,
        0.0F, 0.0F, 0.8F, 1.0F,
        0.0F, 0.0F, 0.7F, 1.0F,
        0.0F, 0.0F, 0.6F, 1.0F,
        0.0F, 0.0F, 0.5F, 1.0F,
        0.0F, 0.0F, 0.4F, 1.0F,
        0.0F, 0.0F, 0.3F, 1.0F,
        0.0F, 0.0F, 0.2F, 1.0F,
        0.0F, 0.0F, 0.1F, 1.0F,
        0.0F, 0.0F, 0.0F, 1.0F,
        0.0F, 0.0F, -1.0F, 1.0F,
        0.0F, 0.0F, -0.9F, 1.0F,
        0.0F, 0.0F, -0.8F, 1.0F,
        0.0F, 0.0F, -0.7F, 1.0F,
        0.0F, 0.0F, -0.6F, 1.0F,
        0.0F, 0.0F, -0.5F, 1.0F,
        0.0F, 0.0F, -0.4F, 1.0F,
        0.0F, 0.0F, -0.3F, 1.0F,
        0.0F, 0.0F, -0.2F, 1.0F,
        0.0F, 0.0F, -0.1F, 1.0F,
        0.0F, 0.0F, 1.0F, -1.0F,
        0.0F, 0.0F, 0.9F, -1.0F,
        0.0F, 0.0F, 0.8F, -1.0F,
        0.0F, 0.0F, 0.7F, -1.0F,
        0.0F, 0.0F, 0.6F, -1.0F,
        0.0F, 0.0F, 0.5F, -1.0F,
        0.0F, 0.0F, 0.4F, -1.0F,
        0.0F, 0.0F, 0.3F, -1.0F,
        0.0F, 0.0F, 0.2F, -1.0F,
        0.0F, 0.0F, 0.1F, -1.0F,
        0.0F, 0.0F, 0.0F, -1.0F,
        0.0F, 0.0F, -1.0F, -1.0F,
        0.0F, 0.0F, -0.9F, -1.0F,
        0.0F, 0.0F, -0.8F, -1.0F,
        0.0F, 0.0F, -0.7F, -1.0F,
        0.0F, 0.0F, -0.6F, -1.0F,
        0.0F, 0.0F, -0.5F, -1.0F,
        0.0F, 0.0F, -0.4F, -1.0F,
        0.0F, 0.0F, -0.3F, -1.0F,
        0.0F, 0.0F, -0.2F, -1.0F,
        0.0F, 0.0F, -0.1F, -1.0F,
    };

// SHADERS -------------------------------------------------------------------

    GLuint shader_program;
    init_default_shaders(&shader_program);

// VBO, VAO ----------------------------------------------------------------------

    GLuint vbo, vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_col), vertex_col, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(0);
    }
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
// -------------------------------------------------------------------------------
    while(!wnd.should_close())
    {        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --  Render  ------------------------------
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, sizeof(vertex_col) / 2);
        // ------------------------------------------

        glfwSwapBuffers(wnd.wnd_ptr());
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);

    glfwTerminate();
    return 0;
}