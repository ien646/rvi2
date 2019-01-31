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
    // Save current selected frame
    rvi::client_context* ctx = inst.get_context();
    rvi::frame* save_ptr = ctx->selected_frame();

    // Return to root frame
    ctx->select_frame(fptr);
    ctx->clear_frame();
    ctx->clear_children();
    ctx->set_position(rvi::vector2(0.10f, 0.15f));
    rvi::standard::print(inst, ctx->selected_frame(), "+-+-+ HELLO FRIEND +-+-+");
    ctx->select_frame(save_ptr);
}

int main()
{
    rvi::window wnd(800, 600, "COZY");

    rvi::runtime rtm;
    int client = rtm.create_client();
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