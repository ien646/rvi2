rvi_check_cmake_ver()

rvi_static_lib("rvi2.serialization")
target_link_libraries("rvi2.serialization" rvi2.core)