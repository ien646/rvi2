# -- SOURCE FILES --
set(RVI2_NET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp_client_win32.cpp   
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp_common_win32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp_connection_win32.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tcp_listener_win32.cpp
)

# -- INCLUDE DIR --
set(RVI2_NET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(rvi2.net STATIC ${RVI2_NET_SOURCES})
target_include_directories(rvi2.net PUBLIC ${RVI2_NET_INCLUDE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -pedantic-errors)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wall -pedantic-errors)  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    #Unsupported
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/W4 /MP)
endif()