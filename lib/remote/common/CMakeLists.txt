rvi_check_cmake_ver()

rvi_static_lib("rvi2.common")
target_link_libraries(rvi2.common rvi2.serialization rvi2.core)