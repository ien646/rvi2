#pragma once

#include "client_instance.hpp"

namespace rvi::std_bindings
{
    extern void print(client_instance& c_inst, const arglist_t& args);
    extern void box_border(client_instance& c_inst, const arglist_t& args);

    extern void init_std_bindings(client_instance& c_inst);
}