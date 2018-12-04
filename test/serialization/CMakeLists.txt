file(GLOB SOURCES src/*.cpp)
add_executable(test.serialization ${SOURCES})
rvi_set_compiler_flags(test.serialization)
target_include_directories(
    test.serialization 
    PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include
    PUBLIC ${CMAKE_BINARY_DIR}/lib/serialization/include)
target_link_libraries(test.serialization rvi2.core rvi2.serialization gtest gmock)
add_test(NAME test.serialization COMMAND test.serialization)