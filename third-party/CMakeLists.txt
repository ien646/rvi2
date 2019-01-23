if(RVI2_BUILD_COZY)
	add_subdirectory(glfw)
endif()

if(RVI2_BUILD_TESTS)
	add_subdirectory(catch2)
endif()