# -- SOURCE FILES --
set(RVI2_CORE_SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/assert.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/base64.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/color_rgba
    ${CMAKE_CURRENT_SOURCE_DIR}/src/frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/line.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/line_container.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rectangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/str_utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/transform2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vector2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/vertex.cpp
)

# -- INCLUDE DIR --
set(RVI2_CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Threads)

add_library(rvi2.core STATIC ${RVI2_CORE_SOURCES})
target_link_libraries(rvi2.core ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(rvi2.core PUBLIC ${RVI2_CORE_INCLUDE_DIR})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -Wextra -Wpedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wall -Wextra -Wpedantic)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    #Unsupported
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/W4 /MP)
endif()