rvi_check_cmake_ver()

rvi_static_lib("rvi2.host")
target_link_libraries(rvi2.host rvi2.core rvi2.serialization)