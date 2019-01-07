file(GLOB SOURCES src/*.cpp)
add_executable(test.serialization ${SOURCES})
target_link_libraries(test.serialization rvi2.core rvi2.serialization gtest gmock)
add_test(NAME test.serialization COMMAND test.serialization)