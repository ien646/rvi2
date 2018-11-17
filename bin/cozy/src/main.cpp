#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <runtime.hpp>
#include <line.hpp>
#include <vertex.hpp>

#include "window.hpp"
#include "shader_utils.hpp"

int main()
{
    window wnd(800, 600, "COZY");

// SHADERS -------------------------------------------------------------------

    GLuint shader_program;
    init_default_shaders(&shader_program);
    
// --- RVI -----------------------------------------------------------------------

    rvi::runtime rtm;

    std::vector<float> vertices;

// --- VERTEX BUFFERS / ARRAYS ---------------------------------------------------

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindVertexArray(NULL);

    glEnable(GL_MULTISAMPLE);
    glLineWidth(2.0F);
    glfwSwapInterval(1);
// -------------------------------------------------------------------------------
    while(!wnd.should_close())
    {        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // --  Render  ------------------------------
        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, sizeof(vertices) * sizeof(float) * 2);
        // ------------------------------------------

        glfwSwapBuffers(wnd.wnd_ptr());
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);

    glfwTerminate();
    return 0;
}