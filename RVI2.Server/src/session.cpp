#include "session.h"

namespace rvi
{
    Session::Session(U64 sessionId)
        : _sessionId(sessionId)
    { }

    void Session::InitProgram(std::stringstream& sstr)
    {
        Interpreter::ParseProgram(sstr, _program);
        _program.ExecOnContext(_context);
    }
}