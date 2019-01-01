set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/cozy)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/cozy)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/cozy)
					   
add_subdirectory("third-party")

file(GLOB SOURCES src/*.cpp src/*.hpp src/*.c src/*.h)
add_executable(cozy ${SOURCES})

rvi_set_compiler_flags(cozy)

target_include_directories(cozy 
	PRIVATE include
	PUBLIC ${CMAKE_BINARY_DIR}/lib/core/include
	PUBLIC third-party/glfw/include)
	
find_package(OpenGL REQUIRED)

set(CXX_STDFS "")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CXX_STDFS stdc++fs)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CXX_STDFS stdc++fs)
endif()
	
target_link_libraries(cozy rvi2.host rvi2.serialization ${CXX_STDFS} rvi2.core glfw ${OPENGL_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

