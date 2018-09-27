set(RVI_MIN_CMAKE_VER "3.7.0")
cmake_minimum_required (VERSION ${RVI_MIN_CMAKE_VER})

message("")
message("****************************************")
message("**               ------               **")
message("**             -  RVI2  -             **")
message("**               ------               **")
message("****************************************")
message("")

set(RVI_PROJ_NAME "rvi2")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/rvi"
					  "${CMAKE_SOURCE_DIR}/cmake_modules/third_party")

include(rvi)

rvi_log(${RVI_PROJ_NAME} "MODULE PATH = ${CMAKE_MODULE_PATH}")

project(${RVI_PROJ_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

rvi_log(${RVI_PROJ_NAME} "INIT PROJECT")

set(RVI_DIR_OUT_SHAREDLIB 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(RVI_DIR_OUT_STATICLIB 	${PROJECT_BINARY_DIR}/output/lib/static)
set(RVI_DIR_OUT_EXECBIN 	${PROJECT_BINARY_DIR}/output/bin)

rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [SHARED LIB] = ${RVI_DIR_OUT_SHAREDLIB}")
rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [STATIC LIB] = ${RVI_DIR_OUT_STATICLIB}")
rvi_log(${RVI_PROJ_NAME} "SET OUTPUT [EXECUTABLE] = ${RVI_DIR_OUT_EXECBIN}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RVI_DIR_OUT_SHAREDLIB})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RVI_DIR_OUT_STATICLIB})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RVI_DIR_OUT_EXECBIN})

add_subdirectory("lib")
add_subdirectory("test")
