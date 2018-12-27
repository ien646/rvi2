rvi_check_cmake_ver()

rvi_static_lib("rvi2.remote.common")
target_link_libraries(rvi2.remote.common rvi2.serialization rvi2.core)