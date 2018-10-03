
file(GLOB SOURCES src/*.cpp src/*.hpp)
add_executable(server_win32 ${SOURCES})

rvi_set_compiler_flags(server_win32)
target_include_directories(server_win32 PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include)
target_link_libraries(server_win32 rvi2.host rvi2.core)