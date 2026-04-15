#ifndef ANTUTU_RHI_WINDOW_HANDLE_H
#define ANTUTU_RHI_WINDOW_HANDLE_H

#include <ANTUTU/Config.hpp>
#include <cstdint>

enum class ANTUTU_API WindowSystemType
{
    GLFW,
    //SDL, for now, we will focus on GLFW, but we can add more window systems in the future.
    WINDOWS,
    X11,
    WAYLAND
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

#endif // ANTUTU_RHI_WINDOW_HANDLE_H