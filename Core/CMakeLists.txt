cmake_minimum_required (VERSION 3.7.0)

# Standard 'conformance' flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")	
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")	
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")
endif()

include_directories(include)
file(GLOB SOURCES src/*.cpp src/*.c include/*.hpp include/*.h)

add_library(RVI2.Core STATIC ${SOURCES})

set_property(TARGET RVI2.Core PROPERTY CXX_STANDARD 17)

cotire(RVI2.Core)

