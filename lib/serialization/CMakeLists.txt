# -- SOURCE FILES --
set(RVI2_SERIALIZATION_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serialization.cpp   
)

# -- INCLUDE FILES --
set(RVI2_SERIALIZATION_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(rvi2.serialization STATIC ${RVI2_SERIALIZATION_SOURCES})
target_include_directories(rvi2.serialization PUBLIC ${RVI2_SERIALIZATION_INCLUDE_DIR})
target_link_libraries(rvi2.serialization rvi2.core)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions(-Wall -pedantic-errors)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_definitions(-Wall -pedantic-errors)  
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    #Unsupported
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(/W4 /MP)
endif()