message("")
message("****************************************")
message("**               ------               **")
message("**             -  RVI2  -             **")
message("**               ------               **")
message("****************************************")
message("")

cmake_minimum_required (VERSION 3.7.0)

set(RVI_PROJ_NAME "rvi2")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_Modules")

include(cotire)
include(rvi)

rvi_log(${RVI_PROJ_NAME} "MODULE PATH = ${CMAKE_MODULE_PATH}")

project(${RVI_PROJ_NAME} LANGUAGES CXX)

rvi_log(${RVI_PROJ_NAME} "INIT PROJECT")

set(RVI_DIR_OUT_SHAREDLIB ${PROJECT_BINARY_DIR}/out/lib/shared)
set(RVI_DIR_OUT_STATICLIB ${PROJECT_BINARY_DIR}/out/lib/static)
set(RVI_DIR_OUT_EXECBIN ${PROJECT_BINARY_DIR}/out/bin)

rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [SHARED LIB] = ${RVI_DIR_OUT_SHAREDLIB}")
rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [STATIC LIB] = ${RVI_DIR_OUT_STATICLIB}")
rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [EXECUTABLE] = ${RVI_DIR_OUT_EXECBIN}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RVI_DIR_OUT_SHAREDLIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RVI_DIR_OUT_STATICLIB})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RVI_DIR_OUT_EXECBIN})

add_subdirectory("lib")