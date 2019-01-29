#pragma once

#include <vector>
#include <functional>

#include <rvi/frame.hpp>

namespace rvi
{
    uint64_t clickable_frame_data_c_uid = 0ul;
    struct clickable_frame_data
    {
        typedef std::function<void(client_instance&)> click_call_t;

        uint64_t uid;
        frame* fptr;
        rectangle rect;
        click_call_t click_call;

        clickable_frame_data(frame* fptr, std::function<void(client_instance&)> call)
            : fptr(fptr)
            , rect(fptr->bounding_rect())
            , click_call(call)
        {  
            uid = clickable_frame_data_c_uid++;
        }
    };
}