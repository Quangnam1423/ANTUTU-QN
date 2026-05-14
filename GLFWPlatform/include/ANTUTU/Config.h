#pragma once

#define COMMON_VERSION_MAJOR 1
#define COMMON_VERSION_MINOR 0
#define COMMON_VERSION_PATCH 0

#if defined(_WIN32)
#define GLFW_PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#elif defined(__ANDROID__)
#define GLFW_PLATFORM_ANDROID
#elif defined(__linux__)
#define GLFW_PLATFORM_LINUX
#else
#error This operating system is not supported by Antutu Engine
#endif


#if (defined(_MSVC_LANG) && _MSVC_LANG < 201703L) || (!defined(_MSVC_LANG) && __cplusplus < 201703L)
	
#endif

////////////////////////////////////////////////////////////
// 3. Portable debug macro
////////////////////////////////////////////////////////////
#if !defined(NDEBUG)
#define GLFW_PLATFORM_DEBUG
#endif

////////////////////////////////////////////////////////////
// 4. Force Inline Macro (Cực quan trọng cho Game Math)
////////////////////////////////////////////////////////////
#if defined(_MSC_VER)
#define GLFW_PLATFORM_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define GLFW_PLATFORM_INLINE inline __attribute__((always_inline))
#else
#define GLFW_PLATFORM_INLINE inline
#endif

////////////////////////////////////////////////////////////
// 5. DLL Export/Import Logic
////////////////////////////////////////////////////////////

// if build static library, then we do nothing here
#if defined(GLFW_PLATFORM_STATIC)
#define GLFW_PLATFORM_API
#else
		// if windows system
#if defined(GLFW_PLATFORM_WINDOWS)
	#if defined(GLFW_PLATFORM_EXPORT)
		#define GLFW_PLATFORM_API __declspec(dllexport)
	#else
		#define GLFW_PLATFORM_API __declspec(dllimport)
	#endif

	#if defined(_MSC_VER)
		#pragma warning(disable : 4251) 
		#pragma warning(disable : 4275)
#endif

//  Linux/Android system/MacOS
#else
#if defined(GLFW_PLATFORM_EXPORT)
#define GLFW_PLATFORM_API __attribute__((visibility("default")))
#else
#define GLFW_PLATFORM_API
#endif
#endif
#endif 