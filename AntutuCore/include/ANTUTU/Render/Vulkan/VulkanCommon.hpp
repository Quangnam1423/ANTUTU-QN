/*
Antutu Vulkan Engine
Copyright (C) 2025 Quangnam1423

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef VULKAN_COMMON_HPP
#define VULKAN_COMMON_HPP

#include "ANTUTU/Config.hpp"



#if defined(ANTUTU_SYSTEM_WINDOWS)

    // define platform macro for vulkan on windows.
    #if !defined(VK_USE_PLATFORM_WIN32_KHR)
    #define VK_USE_PLATFORM_WIN32_KHR       // for Windows.
    #endif

    // prevent windows.h from defining min and max macros
    #if !defined(NOMINMAX)
    #define NOMINMAX
    #endif

    #include <windows.h>                    // for HWND get from windows or surface.

    // include vulkan headers for windows platform.
    #if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
        #include <vulkan/vulkan_raii.hpp>
    #else
        import vulkan_hpp;
    #endif

#elif defined(ANTUTU_SYSTEM_LINUX)
    #define VK_USE_PLATFORM_XLIB_KHR        // for Display*, windows using Xlib ubuntu.
    #include <X11/Xlib.h>               // for Display* get from Xlib.
    // include vulkan headers for linux platform.
    #if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
        #include <vulkan/vulkan_raii.hpp>
    #else
        import vulkan_hpp;
    #endif

#endif

const std::vector<char const*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true; 
#endif

#endif