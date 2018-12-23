#pragma once

#if defined(_WIN32)
    #include "win32/tcp_connection_win32.hpp"
#elif defined(_POSIX_VERSION)
    #include "posix/tcp_connection_posix.hpp"
#endif