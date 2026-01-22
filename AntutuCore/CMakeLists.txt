set(INC_DIR include)
set(SRC_DIR src)

set(COMMON_SRC
    ${INC_DIR}/ANTUTU/Common/NormalMutex.hpp
    ${SRC_DIR}/ANTUTU/Common/NormalMutex.cpp
)

set(RENDER_SRC
    #source and cpp files for classes.
    ${INC_DIR}/ANTUTU/Render/Vulkan/VulkanContext.hpp
    ${SRC_DIR}/ANTUTU/Render/Vulkan/VulkanContext.cpp

    # header only
    ${INC_DIR}/ANTUTU/Render/IVulkanPlatform.hpp
    ${INC_DIR}/ANTUTU/Render/VulkanCommon.hpp
)

set(SYSTEM_SRC
    ${INC_DIR}/ANTUTU/System/Logger.hpp
    ${SRC_DIR}/ANTUTU/System/Logger.cpp
)

set(ROOT_SRC
    ${INC_DIR}/ANTUTU/Config.hpp
    ${SRC_DIR}/ANTUTU/Engine.cpp
    ${INC_DIR}/ANTUTU/Engine.hpp
)

set(ALL_CORE_SOURCES
    ${COMMON_SRC}
    ${SYSTEM_SRC}
    ${RENDER_SRC}
    ${ROOT_SRC}
)

antutu_add_module(AntutuCore
    TYPE SHARED
    SOURCES
        ${ALL_CORE_SOURCES}
    LINK_LIBS
        Vulkan::Vulkan
        glm
        glfw
)

target_compile_definitions(AntutuCore PRIVATE ANTUTU_CORE_EXPORT)

if (WIN32)
    target_compile_definitions(AntutuCore PRIVATE WIN32_LEAN_AND_MEAN)
endif()

target_include_directories(AntutuCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INC_DIR}>
        $<INSTALL_INTERFACE:include/ANTUTU>

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}
)