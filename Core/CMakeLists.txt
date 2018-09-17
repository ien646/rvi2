cmake_minimum_required (VERSION 3.7.0)

include_directories(include)
file(GLOB SOURCES src/*.cpp src/*.c include/*.hpp include/*.h)

add_library(RVI2.Core STATIC ${SOURCES})

set_property(TARGET RVI2.Core PROPERTY CXX_STANDARD 17)

cotire(RVI2.Core)

