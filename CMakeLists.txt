cmake_minimum_required (VERSION 3.7.0)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake_Modules")

include(cotire)

project("RVI2" LANGUAGES CXX)

add_subdirectory("Core")
