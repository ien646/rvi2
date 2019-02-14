#include <glad/glad.hpp> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

#include <rvi/runtime.hpp>
#include <rvi/client_instance.hpp>
#include <rvi/client_context.hpp>
#include <rvi/window.hpp>
#include <rvi/opengl_ctx.hpp>
#include <rvi/standard_library.hpp>

static void hello_click(rvi::client_instance& inst, rvi::frame* fptr)
{
    
}

int main()
{
    rvi::window wnd(800, 600, "COZY");

    rvi::runtime rtm;
    rvi::rvi_cid_t client = rtm.create_client();
    rtm.start_client(client);

    rtm.create_binding("hello_click", &hello_click);

    rvi::opengl_ctx roglctx(&rtm, client);
    roglctx.setup_mouse_callbacks(wnd.wnd_ptr());
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