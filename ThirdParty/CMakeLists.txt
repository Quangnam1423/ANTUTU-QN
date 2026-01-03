message(STATUS "Configuring GLFW...")
option(GLFW_BUILD_DOCS OFF)
option(GLFW_INSTALL OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)


message(STATUS "Configuring GLM...")
option(GLM_TEST_ENABLE OFF)
add_subdirectory(glm)