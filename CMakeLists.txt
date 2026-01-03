# CMake configuration for VulkanEngine
cmake_minimum_required(VERSION 3.15)

message("++ CMake version ${CMAKE_VERSION}")

include(ProcessorCount)

# Define the project name and supported languages
project(Antutu LANGUAGES C CXX)

################################################################################
# Global settings                                                              #
################################################################################
set(ANTUTU_CXX_STD cxx_std_20)

################################################################################
# Output directories                                                          #
################################################################################
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)         # Static Libs (.lib, .a)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)         # Shared Libs (.dll, .so)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)         # Executables (.exe)


################################################################################
# Funcs                                                                        #
################################################################################

# Copy target binary to Binaries folder after build
function(antutu_copy_to_binaries TARGET_NAME)
    if(NOT ANDROID)
        add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/Binaries
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARGET_NAME}> ${CMAKE_BINARY_DIR}/Binaries/
            COMMENT "Copying ${TARGET_NAME} to Binaries folder"
        )
    endif()
endfunction()

# Function to add a module (executable or library) with specified sources and link libraries
function(antutu_add_module target_name)
    set(options)
    set(oneValueArgs TYPE)
    set(multiValueArgs SOURCES LINK_LIBS)

    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARG_TYPE STREQUAL "EXE")
        if(ANDROID)
            add_library(${target_name} SHARED ${ARG_SOURCES})
        else()
            add_executable(${target_name} ${ARG_SOURCES})
            set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/binary)     
            antutu_copy_to_binaries(${target_name})
        endif()
    elseif(ARG_TYPE STREQUAL "STATIC")
        add_library(${target_name} STATIC ${ARG_SOURCES})
    elseif(ARG_TYPE STREQUAL "SHARED")
        add_library(${target_name} SHARED ${ARG_SOURCES})
        string(TOUPPER ${target_name} NAME_UPPER)
        target_compile_definitions(${target_name} PRIVATE ${NAME_UPPER}_EXPORTS)
        antutu_copy_to_binaries(${target_name})

    else()
        message(FATAL_ERROR "antutu_add_module: Unknown TYPE '${ARG_TYPE}' for target '${target_name}'. Use EXE, STATIC, or SHARED.")
    endif()

    if(ARG_LINK_LIBS)
        target_link_libraries(${target_name} PRIVATE ${ARG_LINK_LIBS})
    endif()

    target_compile_features(${target_name} PUBLIC ${ANTUTU_CXX_STD})

endfunction()



################################################################################
# Determin the system to build for. Do that first                              #
################################################################################

if(WIN32)
	if(NOT WINDOWS)
		set(WINDOWS TRUE)
		message("++ Building for windows")
	endif()
elseif(UNIX AND NOT APPLE)
	if(CMAKE_SYSTEM_NAME MATCHES ".*Linux")
		set(LINUX TRUE)
		message("++ Building for Linux")
	elseif(ANDROID)
		message("++ Building for Android")
	else()
		message(FATAL_ERROR "Unknown unix")
	endif()
elseif(APPLE)
	if(CMAKE_SYSTEM_NAME MATCHES ".*MacOS.*")
		set(MACOS TRUE)
		message("++ Building for MacOS")
	else()
		message(FATAL_ERROR "Unknown apple")
	endif()
else()
	message(FATAL_ERROR "Unknown system")
endif()

# Compiler Detection
set(GCC FALSE)
set(CLANG FALSE)
set(CLANG_WINDOWS FALSE)

if(${CMAKE_C_COMPILER_ID} MATCHES "GNU")
	set(GCC TRUE)
	message("++ Compiler identified as GCC")
endif()

if(${CMAKE_C_COMPILER_ID} MATCHES "Clang")
	message("++ Compiler identified as Clang")
	set(CLANG TRUE)
	if(WINDOWS)
		message("++ Compiler identified as Clang for Windows")
		set(CLANG_WINDOWS TRUE)
	endif()
endif()

if(MSVC)
	message("++ Compiler identified as MSVC")
endif()

# Architecture Detection
set(X86 FALSE)
set(ARM FALSE)
if(GCC OR CLANG)
	execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpmachine OUTPUT_VARIABLE target_arch)
	if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch" OR ${target_arch} MATCHES "aarch")
		set(ARM TRUE)
	elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86.*" OR ${CMAKE_SYSTEM_PROCESSOR} MATCHES "AMD64.*")
		set(X86 TRUE)
	else()
		message(FATAL_ERROR "Couldn't find target arch")
	endif()
elseif(MSVC)
	if(${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} MATCHES "arm" OR ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} MATCHES "ARM")
		set(ARM TRUE)
	elseif(${CMAKE_CXX_COMPILER_ARCHITECTURE_ID} MATCHES "x64")
		set(X86 TRUE)
	else()
		message(FATAL_ERROR "Couldn't find target arch")
	endif()
endif()

if(X86)
	message("++ Target architecture is X86")
elseif(ARM)
	message("++ Target architecture is ARM")
endif()


################################################################################
# Configuration                                                                #
################################################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ANTUTU_EXTRA_CHECKS "Debugging checks (assertions)" OFF)
option(ANTUTU_LTO "LTO compilation" OFF)

option(ANTUTU_BUILD_TOOLS "Build tools" ON)
option(ANTUTU_BUILD_TESTS "Build unit tests" OFF)
option(ANTUTU_BUILD_SANDBOX "Build sandbox application" ON)
option(ANTUTU_BUILD_SAMPLES "Build sample applications" ON)

option(ANTUTU_STRIP "Strip the symbols from the executables" OFF)

option(ANTUTU_TRACE "Enable performance tracing" OFF)
if(ANTUTU_TRACE)
	set(_ANTUTU_TRACING_ENABLED 1)
else()
	set(_ANTUTU_TRACING_ENABLED 0)
endif()

option(ANTUTU_STATS "Enable performance statistics" ON)
if(ANTUTU_STATS)
	set(_ANTUTU_STATS_ENABLED 1)
else()
	set(_ANTUTU_STATS_ENABLED 0)
endif()

option(ANTUTU_SIMD "Enable SIMD optimizations" ON)
option(ANTUTU_ADDRESS_SANITIZER "Enable address sanitizer" OFF)
option(ANTUTU_HEADLESS "Build a headless application" OFF)
option(ANTUTU_SHADER_FULL_PRECISION "Build shaders with full precision" OFF)
set(ANTUTU_OVERRIDE_SHADER_COMPILER "" CACHE FILEPATH "Set the ShaderCompiler")
option(ANTUTU_DLSS "Integrate DLSS if supported" OFF)

if(ANDROID)
	option(ANTUTU_PLATFORM_MOBILE "Build for a mobile platform" ON)
else()
	option(ANTUTU_PLATFORM_MOBILE "Build for a mobile platform" OFF)
endif()

# Windowing System
if(ANTUTU_HEADLESS)
	set(SDL FALSE)
elseif(LINUX OR WINDOWS OR MACOS)
	set(SDL TRUE)
elseif(ANDROID)
	set(SDL FALSE)
else()
	message(FATAL_ERROR "Couldn't determine window backend.")
endif()

set(ANTUTU_GR_BACKEND "VULKAN" CACHE STRING "The graphics API to use (VULKAN or DIRECTX)")
option(ANTUTU_D3D_EXPERIMENTAL "Enable some experimental DX features" ON)

if(${ANTUTU_GR_BACKEND} STREQUAL "DIRECTX")
	set(DIRECTX TRUE)
	set(VULKAN FALSE)
elseif(${ANTUTU_GR_BACKEND} STREQUAL "VULKAN")
	set(DIRECTX FALSE)
	set(VULKAN TRUE)  
else()
	message(FATAL_ERROR "Wrong ANTUTU_GR_BACKEND")
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE)
	message(FATAL_ERROR "You need to define CMAKE_BUILD_TYPE")
endif()

################################################################################
# Common compiler & linker flags                                               #
################################################################################

if(MINGW)
	add_compile_options(-mconsole)
endif()

add_definitions(
	-DSPIRV_CROSS_EXCEPTIONS_TO_ASSERTIONS
    -DANTUTU_BUILD
	-DIMGUI_USER_CONFIG=<Antutu/Ui/ImGuiConfig.h>
	-D_CRT_SECURE_NO_WARNINGS=1
)

if(NOT MSVC)
    # --- GCC/Clang ---
	add_compile_options(-Wall -Wextra)
	if(LINUX)
		add_compile_options(-fvisibility=hidden)
	endif()

	# ------Optimization and special flags-------
	# GCC Specific
	if(GCC)
		add_compile_options(-static-libstdc++)
	endif()
	# X86 Specific
	if(X86)
		add_compile_options(-msse4)
	endif()

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

	if(ANTUTU_STRIP)
		add_compile_options(-s)
	endif()
	if(ANTUTU_ADDRESS_SANITIZER)
		add_compile_options(-fsanitize=address)
		add_link_options(-fsanitize=address)
	endif()

	if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		add_compile_options(-O3)
		add_definitions(-DNDEBUG)
	elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		add_compile_options(-O3 -g3 -fno-omit-frame-pointer)
		# set(LINKER_FLAGS "${LINKER_FLAGS} -rdynamic ")
	elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		add_compile_options(-O0 -g3)
		# set(LINKER_FLAGS "${LINKER_FLAGS} -rdynamic ")
	endif()
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
else()

    message(STATUS "++ Configuring specific flags for MSVC...")

    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    add_compile_options(/MP /EHsc /GR- /W4 /FC /Zc:__cplusplus)
    add_definitions(
        -D_CRT_SECURE_NO_WARNINGS=1 
        -DNOMINMAX
    )

    if(${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        add_compile_options(/GS- /Oi /Ob2)
        
        add_definitions(-D_ITERATOR_DEBUG_LEVEL=0) 
    else()
        add_compile_options(/RTC1 /Ob0)
    endif()

endif()

# Linker (Mold/LLD)
if(UNIX AND NOT APPLE)
	execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=lld -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
	execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=mold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE mold_version)
	if("${mold_version}" MATCHES "compatible with GNU")
		message("++ Will use mold linker")
		set(CMAKE_LINKER_TYPE "MOLD")
	elseif("${ld_version}" MATCHES "compatible with GNU linkers")
		message("++ Will use LLD linker")
		set(CMAKE_LINKER_TYPE "LLD")
	endif()
endif()

if(ANTUTU_LTO)
	set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

################################################################################
# Thirdparty                                                                   #
################################################################################

add_subdirectory(ThirdParty)

find_package(Vulkan REQUIRED)
message("++ Found Vulkan: ${Vulkan_INCLUDE_DIRS}")

################################################################################
# Global includes                                                              #
################################################################################


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Vulkan_INCLUDE_DIRS}
)

################################################################################
# BUILD OPTIONS                                                                #
################################################################################

option(ANTUTU_BUILD_SANDBOX "Build the sandbox application" ON)
option(ANTUTU_BUILD_CSHARP_BINDINGS "Build C# Interop DLL" ON)
option(ANTUTU_BUILD_TESTS "Build unit tests" OFF)


################################################################################
# Subdirectories                                                               #
################################################################################

add_subdirectory(AntutuCore)

if(ANTUTU_BUILD_CSHARP_BINDING)
    add_subdirectory(AntutuInterop)
endif()

if(ANTUTU_BUILD_SANDBOX AND NOT ANDROID)
    add_subdirectory(Sandbox)
endif()
