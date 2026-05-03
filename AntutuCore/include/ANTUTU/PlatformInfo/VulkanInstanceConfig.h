#ifndef ANTUTU_PLATFORM_INFO_VULKAN_INSTANCE_CONFIG_HPP
#define ANTUTU_PLATFORM_INFO_VULKAN_INSTANCE_CONFIG_HPP

#include <ANTUTU/VulkanCommon.hpp>

namespace att::PlatformInfo
{
    struct ANTUTU_API VulkanInstanceConfig
    {
        const char* appName;
        uint32_t appVer;
        const char* engineName;
        uint32_t engineVer;
        uint32_t apiVer;
        std::vector<const char*> exts;
    };
}

#endif // ANTUTU_PLATFORM_INFO_VULKAN_INSTANCE_CONFIG_HPP