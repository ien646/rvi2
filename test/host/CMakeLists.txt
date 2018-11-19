file(GLOB SOURCES src/*.cpp)
add_executable(test.host ${SOURCES})
rvi_set_compiler_flags(test.host)
target_include_directories(
    test.host 
    PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include
    PUBLIC ${CMAKE_BINARY_DIR}/lib/host/include)
target_link_libraries(test.host rvi2.core rvi2.host gtest gmock)
add_test(NAME test.host COMMAND test.host)