rvi_check_cmake_ver()

rvi_static_lib("rvi2.remote.tcp_client")

target_link_libraries(rvi2.remote.tcp_client rvi2.core rvi2.serialization rvi2.net)