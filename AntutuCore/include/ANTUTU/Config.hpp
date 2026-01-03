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

#pragma once

// engine version
#define ANTUTU_VERSION_MAJOR 1
#define ANTUTU_VERSION_MINOR 0
#define ANTUTU_VERSION_PATCH 0

////////////////////////////////////////////////////////////
// 1. Identify the operating system
////////////////////////////////////////////////////////////
#if defined(_WIN32)
    #define ANTUTU_SYSTEM_WINDOWS
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif

#elif defined(__ANDROID__)
    #define ANTUTU_SYSTEM_ANDROID
    // Android cũng là Linux-based, nhưng ta tách riêng để dễ xử lý

#elif defined(__linux__)
    #define ANTUTU_SYSTEM_LINUX

#else
    #error This operating system is not supported by Antutu Engine
#endif

////////////////////////////////////////////////////////////
// 2. Ensure minimum C++17
////////////////////////////////////////////////////////////
#if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
    #error "Antutu Engine requires C++17 or newer."
#endif

////////////////////////////////////////////////////////////
// 3. Portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)
    #define ANTUTU_DEBUG
#endif

////////////////////////////////////////////////////////////
// 4. Force Inline Macro (Cực quan trọng cho Game Math)
////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
    #define ANTUTU_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
    #define ANTUTU_INLINE inline __attribute__((always_inline))
#else
    #define ANTUTU_INLINE inline
#endif

////////////////////////////////////////////////////////////
// 5. DLL Export/Import Logic
////////////////////////////////////////////////////////////

// if build static library, then we do nothing here
#if defined(ANTUTU_STATIC)
    #define ANTUTU_API
#else
    // if windows system
    #if defined(ANTUTU_SYSTEM_WINDOWS)
        
        #if defined(ANTUTU_CORE_EXPORT)
            #define ANTUTU_API __declspec(dllexport)
        #else
            #define ANTUTU_API __declspec(dllimport)
        #endif

        // Tắt cảnh báo khi export STL (std::vector, std::string)
        #if defined(_MSC_VER)
            #pragma warning(disable : 4251) 
            #pragma warning(disable : 4275)
        #endif

    //  Linux/Android system/MacOS
    #else
        #if defined(ANTUTU_CORE_EXPORT)
            #define ANTUTU_API __attribute__((visibility("default")))
        #else
            #define ANTUTU_API
        #endif
    #endif
#endif 
