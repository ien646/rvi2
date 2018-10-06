rvi_check_cmake_ver()

rvi_static_lib("rvi2.client")
target_link_libraries(rvi2.client rvi2.core rvi2.serialization)