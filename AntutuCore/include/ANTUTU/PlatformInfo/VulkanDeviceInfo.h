#ifndef ANTUTU_RHI_VULKAN_DEVICE_INFO_HPP
#define ANTUTU_RHI_VULKAN_DEVICE_INFO_HPP

#include <ANTUTU/VulkanCommon.hpp>

namespace att::PlatformInfo
{
    struct VulkanDeviceInfo
    {
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        std::vector<VkQueueFamilyProperties> queueFamilies;
        std::vector<VkExtensionProperties> extensions;
    };

    VulkanDeviceInfo QueryVulkanDeviceInfo(VkPhysicalDevice device);
}

#endif // ANTUTU_RHI_VULKAN_DEVICE_INFO_HPP