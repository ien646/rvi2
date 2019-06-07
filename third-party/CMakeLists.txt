if(RVI2_BUILD_COZY)

    option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
    option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
    option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
    option(GLFW_INSTALL "Generate installation target" OFF)
    option(GLFW_VULKAN_STATIC "Use the Vulkan loader statically linked into application" OFF)

	add_subdirectory(glfw)
endif()

if(RVI2_BUILD_TESTS)
	add_subdirectory(catch2)
endif()

add_subdirectory(lua)

add_definitions(-DSOL_USING_CXX_LUA)
add_subdirectory(sol2)

option(BENCHMARK_ENABLE_TESTING "..." OFF)
option(BENCHMARK_ENABLE_GTEST_TESTS "..." OFF)
add_subdirectory(benchmark)