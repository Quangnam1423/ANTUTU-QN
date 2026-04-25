#ifndef ANTUTU_PLATFORM_INFO_VULKAN_DEBUG_CONFIG_HPP
#define ANTUTU_PLATFORM_INFO_VULKAN_DEBUG_CONFIG_HPP

#include <ANTUTU/VulkanCommon.hpp>


namespace att::PlatformInfo
{
    struct ANTUTU_API VulkanDebugConfig
    {
        bool enable = true;

        VkDebugUtilsMessageSeverityFlagsEXT msgSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        VkDebugUtilsMessageTypeFlagsEXT type = 
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    };
}

#endif  // ANTUTU_PLATFORM_INFO_VULKAN_DEBUG_CONFIG_HPP