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

#define ANTUTU_VERSION_MAJOR 1
#define ANTUTU_VERSION_MINOR 0
#define ANTUTU_VERSION_PATCH 0

////////////////////////////////////////////////////////////
// Identify the operating system (Windows and Linux only)
////////////////////////////////////////////////////////////
#if defined(_WIN32)

// Windows
#define ANTUTU_SYSTEM_WINDOWS

#ifndef NOMINMAX
#define NOMINMAX
#endif

#elif defined(__linux__)

// Linux
#define ANTUTU_SYSTEM_LINUX

#else

// Unsupported system
#error This operating system is not supported by Antutu Engine (Only Windows and Linux are supported)

#endif

////////////////////////////////////////////////////////////
// Ensure minimum C++ language standard version is met
////////////////////////////////////////////////////////////
#if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
#error "Enable C++17 or newer for your compiler (e.g. -std=c++17 for GCC/Clang or /std:c++17 for MSVC)"
#endif

////////////////////////////////////////////////////////////
// Portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)

#define ANTUTU_DEBUG

#endif

////////////////////////////////////////////////////////////
// Helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if !defined(ANTUTU_STATIC)

#if defined(ANTUTU_SYSTEM_WINDOWS)

// Windows compilers need specific (and different) keywords for export and import
#define ANTUTU_API_EXPORT __declspec(dllexport)
#define ANTUTU_API_IMPORT __declspec(dllimport)

// For Visual C++ compilers, we also need to turn off this annoying C4251 & C4275 warning
#ifdef _MSC_VER

#pragma warning(disable : 4251) // Using standard library types in our own exported types is okay
#pragma warning(disable : 4275) // Exporting types derived from the standard library is okay

#endif

#else // Linux, FreeBSD, macOS, etc.

#define ANTUTU_API_EXPORT __attribute__((visibility("default")))
#define ANTUTU_API_IMPORT __attribute__((visibility("default")))

#endif

#else

// Static build, so no import/export macros needed
#define ANTUTU_API_EXPORT
#define ANTUTU_API_IMPORT

#endif