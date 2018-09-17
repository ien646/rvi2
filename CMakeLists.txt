message("")
message("+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+")
message("+-              RVI2              -+")
message("+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+")
message("")

cmake_minimum_required (VERSION 3.7.0)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_Modules")

message(">> MODULE PATH = ${CMAKE_MODULE_PATH}")

include(cotire)

project("RVI2" LANGUAGES CXX)

message(">> INIT PROJECT")

set(RVI_DIR_OUT_SHAREDLIB ${PROJECT_BINARY_DIR}/out/lib/shared)
set(RVI_DIR_OUT_STATICLIB ${PROJECT_BINARY_DIR}/out/lib/static)
set(RVI_DIR_OUT_EXECBIN ${PROJECT_BINARY_DIR}/out/bin)

message(">> SET OUTPUT [SHARED LIB] = ${RVI_DIR_OUT_SHAREDLIB}")
message(">> SET OUTPUT [STATIC LIB] = ${RVI_DIR_OUT_STATICLIB}")
message(">> SET OUTPUT [EXECUTABLE] = ${RVI_DIR_OUT_EXECBIN}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RVI_DIR_OUT_SHAREDLIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RVI_DIR_OUT_STATICLIB})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RVI_DIR_OUT_EXECBIN})

add_subdirectory("Core")

