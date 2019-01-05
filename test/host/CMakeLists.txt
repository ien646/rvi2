file(GLOB SOURCES src/*.cpp)
add_executable(test.host ${SOURCES})
target_link_libraries(test.host rvi2.core rvi2.host gtest gmock)
add_test(NAME test.host COMMAND test.host)