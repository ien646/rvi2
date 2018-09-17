#pragma once

#include <sstream>

#include "rvi_base.h"
#include "client_context.h"
#include "program.h"

namespace rvi
{
    class Session
    {
    private:
        ClientContext _context;
        U64 _sessionId = 0;
        Program _program;

    public:
        Session() = delete;
        Session(U64 sessionId);

        void InitProgram(std::stringstream& sstr);
    };
}