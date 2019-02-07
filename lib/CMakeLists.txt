add_subdirectory("core")
add_subdirectory("host")
add_subdirectory("serialization")

if(RVI2_BUILD_COZY)
	add_subdirectory("cozy")
endif()