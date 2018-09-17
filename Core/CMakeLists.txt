message("")

cmake_minimum_required (VERSION 3.7.0)

message(">> [RVICORE]: DETECTED C++ COMPILER: [${CMAKE_CXX_COMPILER_ID}]")

# Standard 'conformance' flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")	
	set(RVICORE_CONFORMANCE_FLAG "/permissive-")	
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(RVICORE_CONFORMANCE_FLAG "-pedantic-errors")	
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(RVICORE_CONFORMANCE_FLAG "-pedantic-errors")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RVICORE_CONFORMANCE_FLAG}")
message(">> [RVICORE]: SET CPP-STD CONFORMANCE FLAG (${RVICORE_CONFORMANCE_FLAG}) FOR COMPILER ${CMAKE_CXX_COMPILER_ID}")

include_directories(include)
file(GLOB SOURCES src/*.cpp src/*.c include/*.hpp include/*.h)

add_library(RVI2.Core STATIC ${SOURCES})

set_property(TARGET RVI2.Core PROPERTY CXX_STANDARD 17)

cotire(RVI2.Core)