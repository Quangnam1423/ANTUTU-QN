set(INC_DIR include)
set(SRC_DIR src)

set(RENDER_SRC
    # interfaces
    ${INC_DIR}/ANTUTU/Render/IRender.hpp
)

set(ROOT_SRC
    # header only
    ${INC_DIR}/ANTUTU/VulkanCommon.hpp
    ${INC_DIR}/ANTUTU/Config.hpp
)

set(RHI_SRC
    #interfaces
    ${INC_DIR}/ANTUTU/RHI/ISurfaceProvider.hpp

    #headers only
    ${INC_DIR}/ANTUTU/RHI/InstanceDescriptor.hpp
    ${INC_DIR}/ANTUTU/RHI/WindowHandle.h

    ${INC_DIR}/ANTUTU/RHI/VulkanInstance.hpp
    ${SRC_DIR}/ANTUTU/RHI/VulkanInstance.cpp

    ${INC_DIR}/ANTUTU/RHI/VulkanContext.hpp
    ${SRC_DIR}/ANTUTU/RHI/VulkanContext.cpp

    ${INC_DIR}/ANTUTU/RHI/VulkanSurface.hpp
    ${SRC_DIR}/ANTUTU/RHI/VulkanSurface.cpp

    ${INC_DIR}/ANTUTU/RHI/VulkanRender.hpp
    ${SRC_DIR}/ANTUTU/RHI/VulkanRender.cpp
)

set(ALL_CORE_SOURCES
    ${SYSTEM_SRC}
    ${RENDER_SRC}
    ${ROOT_SRC}
    ${RHI_SRC}
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