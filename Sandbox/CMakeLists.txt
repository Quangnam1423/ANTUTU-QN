set(INC_DIR include)
set(SRC_DIR src)

set(WINDOW_MODULE

)

set(OBJECT_MODULE
    ${INC_DIR}/Object/Window.hpp
    ${SRC_DIR}/Object/Window.cpp
)

set(SANDBOX_MANAGER_MODULE
    ${INC_DIR}/SandboxManager/WindowManager.hpp
    ${SRC_DIR}/SandboxManager/WindowManager.cpp
)


set(STATE_MODULE
    ${INC_DIR}/State/ISandBoxState.hpp

    ${INC_DIR}/State/SandBoxState.hpp
    ${INC_DIR}/State/IntroduceState.hpp
)

set(SANDBOX_MODULE

)

set(ROOT_SRC
    ${INC_DIR}/Sandbox.hpp
    ${SRC_DIR}/Sandbox.cpp
    ${SRC_DIR}/main.cpp
)

set(ALL_SANDBOX_SRC
    ${WINDOW_MODULE}
    ${SANDBOX_MANAGER_MODULE}
    ${OBJECT_MODULE}
    ${SANDBOX_MODULE}
    ${ROOT_SRC}
)

antutu_add_module(Sandbox
    TYPE EXE
    SOURCES
        ${ALL_SANDBOX_SRC}
    LINK_LIBS
        AntutuCommon
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