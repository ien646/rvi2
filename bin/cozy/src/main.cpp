#include <glad/glad.hpp> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

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
    
    // vsync
    glfwSwapInterval(1);

    auto clk = std::chrono::high_resolution_clock();
    auto i_time = clk.now();

    while(!wnd.should_close())
    {
        auto delta_duration = (clk.now() - i_time).count();
        auto delta_time = static_cast<float>(delta_duration) / 1000000.0F;
        // --  Render  ------------------------------
        roglctx.refresh();
        roglctx.draw(delta_time);
        // ------------------------------------------
        glfwSwapBuffers(wnd.wnd_ptr());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}