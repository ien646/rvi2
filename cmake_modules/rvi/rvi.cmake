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
	
		add_definitions(-pedantic-errors -Wall)
		
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	
		add_definitions(-pedantic-errors -Wall)
		
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
	
	target_include_directories(${RVI_LIB_NAME} PUBLIC ./include)
	rvi_footer(${RVI_LIB_NAME})
	file(COPY ${HEADERS} DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/include)
endfunction()

function("rvi_check_cmake_ver")
	cmake_minimum_required (VERSION ${RVI_MIN_CMAKE_VER})
endfunction()
