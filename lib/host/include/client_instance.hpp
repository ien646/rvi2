#pragma once

#include <client_context.hpp>

#include "client_instance_data.hpp"

namespace rvi
{
    class runtime; // fwd

    class client_instance
    {
    private:
        runtime* _runtime_ptr;

    public:
        client_context context;
        client_instance_data data;

        client_instance(runtime* rptr);

        // -- include control --
        void push_include(const std::string& inc_file);
        const std::string& peek_current_include() const;
        void pop_include();
        void mark_include_once();
        runtime* runtime_ptr();

        void exec_definition(const std::string& dname);

        void exec_binding(const std::string& bname, const arglist_t& args);

        void set_clickable_frame(
            frame* fptr, 
            const std::string& binding_name,
            float depth,
            const std::vector<std::string>& binding_args);
            
        void unset_clickable_frame(frame* fptr);

        void user_click(vector2 pos);

        void key_press(char kval);
    };
}