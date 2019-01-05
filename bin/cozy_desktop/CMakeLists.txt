set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/cozy_desktop)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/cozy_desktop)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/cozy_desktop)
					   
file(GLOB SOURCES src/*.cpp src/*.hpp src/*.c src/*.h)
add_executable(cozy_desktop ${SOURCES})

target_link_libraries(cozy_desktop rvi2.cozy)

get_property(RVI2_COZY_SHADERS_DIR GLOBAL PROPERTY RVI2_COZY_SHADERS_DIR)

file(COPY ${RVI2_DATA_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${RVI2_COZY_SHADERS_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})