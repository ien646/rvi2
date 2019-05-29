set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/simd_bench)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/simd_bench)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/simd_bench)
					   
file(GLOB SOURCES src/*.cpp src/*.hpp src/*.c src/*.h)
add_executable(simd_bench ${SOURCES})

target_link_libraries(simd_bench rvi2.core)