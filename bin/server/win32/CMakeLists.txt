set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/server_win32)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/server_win32)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/server_win32)

file(GLOB SOURCES src/*.cpp src/*.hpp)
add_executable(server_win32 ${SOURCES})

rvi_set_compiler_flags(server_win32)
target_include_directories(server_win32 PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include)
target_link_libraries(server_win32 rvi2.host rvi2.core)
add_custom_command(TARGET server_win32 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:server_win32>/data)