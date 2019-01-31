#pragma once

#include <vector>
#include <functional>

#include <rvi/frame.hpp>
namespace rvi
{
    class client_instance; //fwd
    typedef std::function<void(client_instance&)> click_call_t;

    uint64_t _clickable_frame_data_c_uid = 0ul;

    struct clickable_frame_data
    {
        uint64_t uid;
        frame* fptr;
        rectangle rect;
        std::string binding_name;

        clickable_frame_data(frame* fptr, const std::string& binding_name)
            : fptr(fptr)
            , rect(fptr->bounding_rect())
            , binding_name(binding_name)
        {  
            uid = _clickable_frame_data_c_uid++;
        }
    };
}