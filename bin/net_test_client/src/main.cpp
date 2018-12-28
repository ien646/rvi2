#include <thread>
#include <functional>
#include <iostream>

#include "rvi_tcp_client.hpp"
#include "msg_header.hpp"

using namespace rvi;

static void msg_callback(tcp_connection conn, message_data_t&& msg)
{
    switch(static_cast<msg_header>(msg[0]))
    {
        case msg_header::BEGIN_SEQUENCE:
            break;
        case msg_header::END_SEQUENCE:
            break;

        case msg_header::SELECT_FRAME:
            break;
        case msg_header::RELEASE_FRAME:
            break;
        case msg_header::DELETE_FRAME:
            break;
        
        case msg_header::DRAW_LINE:
            break;
        case msg_header::DRAW_LINES:
            break;

        case msg_header::DISCONNECT:
            break;

        case msg_header::UNKNOWN_ERROR:
            break;

        default:
            break;
    }
}

int main()
{
    while(true)
    {
        rvi_tcp_client client("127.0.0.1", 8787);
        client.setup_msg_callback(&msg_callback);
        client.connect();
    }
}

