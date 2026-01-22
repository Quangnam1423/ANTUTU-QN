#ifndef VULKAN_COMMON_HPP
#define VULKAN_COMMON_HPP

#include "ANTUTU/Config.hpp"

#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
    #include <vulkan/vulkan_raii.hpp>
#else
    import vulkan_hpp;
#endif

#endif