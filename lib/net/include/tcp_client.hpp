#pragma once

#if defined(_WIN32)
    #include "tcp_client_win32.hpp"
#elif defined(_POSIX_VERSION)
    #include "tcp_client_posix.hpp"
#endif