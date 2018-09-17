cmake_minimum_required (VERSION 3.11)

include_directories(include)
file(GLOB SOURCES src/*.cpp)

add_library(RVI2.Core STATIC ${SOURCES})