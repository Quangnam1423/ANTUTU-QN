set(INC_DIR include)
set(SRC_DIR src)

set(PLATFORM_GLFW_SOURCES
    ${INC_DIR}/ANTUTU/Config.h
    ${INC_DIR}/ANTUTU/GLFWWindow.hpp
    ${SRC_DIR}/ANTUTU/GLFWWindow.cpp
)

antutu_add_module(antutu_platform_GLFW
    TYPE SHARED
    SOURCES
        ${PLATFORM_GLFW_SOURCES}
    LINK_LIBS
        AntutuCommon
        AntutuCore
        glfw
)

target_compile_definitions(antutu_platform_GLFW PRIVATE GLFW_PLATFORM_EXPORT)

target_include_directories(antutu_platform_GLFW
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INC_DIR}>
        $<INSTALL_INTERFACE:include/ANTUTU>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}
)