set(RVI_MIN_CMAKE_VER "3.7.0")
cmake_minimum_required (VERSION ${RVI_MIN_CMAKE_VER})

message("")
message("****************************************")
message("**               ------               **")
message("**             -  RVI2  -             **")
message("**               ------               **")
message("****************************************")
message("")

set(RVI_PROJ_NAME "rvi2")

project(rvi2 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin/no-category)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin/no-category)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/shared)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/static)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin/no-category)

set(RVI2_DATA_DIR ${PROJECT_SOURCE_DIR}/data)

add_subdirectory("third-party")
add_subdirectory("lib")
add_subdirectory("bin")
add_subdirectory("test")
