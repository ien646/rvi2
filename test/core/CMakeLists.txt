set(TEST_RVI2_CORE_SOURCES
    src/main.cpp
    src/vector2.cpp
    src/math.cpp
    src/frame.cpp
    src/line_container.cpp
)

find_package(Threads)

add_executable(test.rvi2.core ${TEST_RVI2_CORE_SOURCES})
target_link_libraries(test.rvi2.core rvi2.core Threads::Threads Catch2::Catch2)