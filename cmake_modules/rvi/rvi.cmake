function("rvi_log" LOG_SOURCE MSG)
	message(">> [${LOG_SOURCE}]: ${MSG}")
endfunction()

function("rvi_header" TEXT)
	message("-------------------------------------")
	message("******** [${TEXT}]")
	message("-------------------------------------")
endfunction()

function("rvi_footer" TEXT)
	message(">> COMPLETE: [${TEXT}]")
	message("-------------------------------------")
endfunction()

function("rvi_set_compiler_flags" TARGETNAME)

	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")	
	
		add_definitions(/permissive- /W4 /MP /Gm-)	
		
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	
		add_definitions(-pedantic-errors -Wall -lstdc++fs -std=c++17)
		
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	
		add_definitions(
			-std=c++17 
			-pedantic-errors 
			-Wall
			-lstdc++fs 
			-Wno-c++98-compat 
			-Wno-c++98-compat-pedantic
			-Wno-newline-eof)
			
	endif()
	
	rvi_log(${TARGETNAME} "SET COMPILER FLAGS FOR ${CMAKE_CXX_COMPILER_ID}")
endfunction()

function("rvi_static_lib" RVI_LIB_NAME)
	
	rvi_header(${RVI_LIB_NAME})
	
	rvi_log(${RVI_LIB_NAME} "DETECTED C++ COMPILER: [${CMAKE_CXX_COMPILER_ID}]")
	
	rvi_set_compiler_flags(${RVI_LIB_NAME})	
	
	file(GLOB SOURCES src/*.cpp src/*.c src/*.hpp src/*.h include/*.hpp include/*.h)
	file(GLOB HEADERS include/*)
	
	message(">> [SOURCES]:")
	foreach(ITEM ${SOURCES})
		message("    - ${ITEM}")
	endforeach()	
	message(">> [HEADERS]:")
	foreach(ITEM ${HEADERS})
		message("   - ${ITEM}")
	endforeach()	
	
	add_library(${RVI_LIB_NAME} STATIC ${SOURCES})
	
	set_property(TARGET ${RVI_LIB_NAME} PROPERTY CXX_STANDARD 17)
	set_property(TARGET ${RVI_LIB_NAME} PROPERTY LINKER_LANGUAGE CXX)
	
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/shared)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/lib/static)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 			${PROJECT_BINARY_DIR}/output/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/shared)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/lib/static)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG 	${PROJECT_BINARY_DIR}/output/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/shared)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/lib/static)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE 	${PROJECT_BINARY_DIR}/output/bin)
	
	target_include_directories(${RVI_LIB_NAME} PUBLIC ./include)
	rvi_footer(${RVI_LIB_NAME})
	file(COPY ${HEADERS} DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/include/${RVI_LIB_NAME})
endfunction()

function("rvi_check_cmake_ver")
	cmake_minimum_required (VERSION ${RVI_MIN_CMAKE_VER})
endfunction()
