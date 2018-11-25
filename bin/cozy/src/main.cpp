#include <glad/glad.hpp> 
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
#include "opengl_ctx.hpp"

int main()
{
    window wnd(800, 600, "COZY");

    rvi::runtime rtm;
    int client = rtm.create_client();
    rtm.start_client(client);   
    
    rvi::opengl_ctx roglctx(&rtm, client);
    roglctx.refresh();
    
    glfwSwapInterval(1);
    while(!wnd.should_close())
    {
        // --  Render  ------------------------------
        roglctx.refresh();
        roglctx.draw();
        // ------------------------------------------
        glfwSwapBuffers(wnd.wnd_ptr());
        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);

    glfwTerminate();
    return 0;
}