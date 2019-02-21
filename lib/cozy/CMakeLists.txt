# -- SOURCE FILES --
set(RVI2_COZY_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl_ctx.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vframe.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
)

set_property(GLOBAL PROPERTY RVI2_COZY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_property(GLOBAL PROPERTY RVI2_COZY_SHADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)

add_library(rvi2.cozy STATIC ${RVI2_COZY_SOURCES})
target_include_directories(rvi2.cozy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(rvi2.cozy rvi2.host glfw)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -Wextra -Wpedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wall -Wextra -Wpedantic)  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    #Unsupported
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/W4 /MP)
endif()