rvi_check_cmake_ver()

rvi_static_lib("rvi2.net")
target_link_libraries(rvi2.net rvi2.core rvi2.serialization)