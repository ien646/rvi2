#include <glad/glad.hpp> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>

#include <rvi/runtime.hpp>
#include <rvi/line.hpp>
#include <rvi/vertex.hpp>

#include <rvi/window.hpp>
#include <rvi/opengl_ctx.hpp>

static void hello_click(rvi::client_instance& inst, const rvi::arglist_t&)
{
    // Save current selected frame
    auto& ctx = inst.context;
    rvi::frame* save_ptr = ctx.selected_frame();

    // Return to root frame
    ctx.select_frame("hello_friend");
    ctx.clear_frame();
    ctx.clear_children();
    ctx.set_position(rvi::vector2(0.10f, 0.15f));
    inst.exec_binding("printx", rvi::arglist_t
    {
        "+-+-+ HELLO FRIEND +-+-+",
        "0.02"
    });
    ctx.select_frame(save_ptr);
}

int main()
{
    rvi::window wnd(800, 600, "COZY");

    rvi::runtime rtm;
    int client = rtm.create_client();
    rtm.start_client(client);

    rtm.get_instance(client).create_binding("hello_click", &hello_click);

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