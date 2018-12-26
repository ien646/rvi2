set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/net_test_client)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/net_test_client)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/net_test_client)
					   
file(GLOB SOURCES src/*.cpp src/*.hpp)
add_executable(net_test_client ${SOURCES})

rvi_set_compiler_flags(net_test_client)

target_include_directories(net_test_client
	PRIVATE include
	PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include
	PUBLIC ${CMAKE_BINARY_DIR}/lib/serialization/include
	PUBLIC ${CMAKE_BINARY_DIR}/lib/net/include)
	
target_link_libraries(net_test_client rvi2.net)