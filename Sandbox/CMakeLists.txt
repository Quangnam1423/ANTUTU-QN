set(INC_DIR include)
set(SRC_DIR src)

set(WINDOW_MODULE
    ${INC_DIR}/window/Window.hpp
    ${SRC_DIR}/window/Window.cpp
)

set(STATE_MODULE
    ${INC_DIR}/states/ISandBoxState.hpp

    ${INC_DIR}/states/SandBoxState.hpp
    ${INC_DIR}/states/IntroduceState.hpp
)

set(SANDBOX_MODULE
    ${INC_DIR}/sandbox/Sandbox.hpp
    ${SRC_DIR}/sandbox/Sandbox.cpp
)

set(ROOT_SRC
    ${SRC_DIR}/main.cpp
)

set(ALL_SANDBOX_SRC
    ${WINDOW_MODULE}
    ${SANDBOX_MODULE}
    ${ROOT_SRC}
)

antutu_add_module(Sandbox
    TYPE EXE
    SOURCES
        ${ALL_SANDBOX_SRC}
    LINK_LIBS
        AntutuCore
        Vulkan::Vulkan
        glfw
        glm
)

target_compile_definitions(Sandbox PRIVATE 
    VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
)

target_include_directories(Sandbox PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)