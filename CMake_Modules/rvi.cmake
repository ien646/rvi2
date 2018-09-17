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

function("rvi_set_stdconf_mode" TARGETNAME)
	# Standard 'conformance' flags
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")	
		set(RVICORE_CONFORMANCE_FLAG "/permissive-")	
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(RVICORE_CONFORMANCE_FLAG "-pedantic-errors")	
	elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(RVICORE_CONFORMANCE_FLAG "-pedantic-errors")
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RVICORE_CONFORMANCE_FLAG}")
	rvi_log(${TARGETNAME} "SET CPP-STD CONFORMANCE FLAG (${RVICORE_CONFORMANCE_FLAG}) FOR COMPILER ${CMAKE_CXX_COMPILER_ID}")
endfunction()

function("rvi_static_lib" RVI_LIB_NAME)
	rvi_header(${RVI_LIB_NAME})
	
	rvi_log(${RVI_LIB_NAME} "DETECTED C++ COMPILER: [${CMAKE_CXX_COMPILER_ID}]")
	
	rvi_set_stdconf_mode(${RVI_LIB_NAME})
	
	include_directories(include)
	
	file(GLOB SOURCES src/*.cpp src/*.c include/*.hpp include/*.h)
	add_library(${RVI_LIB_NAME} STATIC ${SOURCES})	
	
	set_property(TARGET ${RVI_LIB_NAME} PROPERTY CXX_STANDARD 17)
	set_property(TARGET ${RVI_LIB_NAME} PROPERTY LINKER_LANGUAGE CXX)
	
	cotire(${RVI_LIB_NAME})
	
	rvi_footer(${RVI_LIB_NAME})
endfunction()