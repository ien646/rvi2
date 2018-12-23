#pragma once

#if !defined(_WIN32)
#error "Unable to use Windows tcp_client on non Windows compatible platform"
#endif

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// ... TODO ...