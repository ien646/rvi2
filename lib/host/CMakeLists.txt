# -- SOURCE FILES --
set(RVI2_HOST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client_instance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/standard_library.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lua_context.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/runtime.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/clickable_frame_data.cpp
)

# -- INCLUDE DIR --
set(RVI2_HOST_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(rvi2.host STATIC ${RVI2_HOST_SOURCES})
target_include_directories(rvi2.host PUBLIC ${RVI2_HOST_INCLUDE_DIR})
target_link_libraries(rvi2.host rvi2.core sol2 lua)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -pedantic-errors)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wall -pedantic-errors)  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    #Unsupported
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/W4 /MP)
endif()