#ifndef VULKAN_PLATFORM_INFO_VULKAN_SURFACE_CONFIG_HPP
#define VULKAN_PLATFORM_INFO_VULKAN_SURFACE_CONFIG_HPP

#include <ANTUTU/VulkanCommon.hpp>

namespace att::PlatformInfo
{
    struct ANTUTU_API VulkanSurfaceConfig
    {
        void* windowHandle = nullptr;
    };

    enum class ANTUTU_API WindowSystemType
    {
        WINDOWS,
        X11,
        WAYLAND,
        GLFW
    };

    struct ANTUTU_API WindowHandle
    {
        WindowSystemType systemType;
        union
        {
            struct { void* hwnd; void* hinstance; } win32;
            struct { void* display; void* window; } x11;
            struct { void* display; void* surface; } wayland;
            struct { void* window; } glfw;
        };
    };
}

#endif // VULKAN_PLATFORM_INFO_VULKAN_SURFACE_CONFIG_HPP