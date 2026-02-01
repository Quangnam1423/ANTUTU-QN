set(INC_DIR include)
set(SRC_DIR src)

set(ALL_CORE_SOURCES
    main.cpp
    # ${COMMON_SRC}
    # ${SYSTEM_SRC}
    # ${RENDER_SRC}
    # ${ROOT_SRC}
)

antutu_add_module(Tests
    TYPE EXE
    SOURCES
        ${ALL_CORE_SOURCES}
    LINK_LIBS
        Vulkan::Vulkan
        glm
        glfw
)   

target_compile_definitions(Tests PRIVATE VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)

target_include_directories(Tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)