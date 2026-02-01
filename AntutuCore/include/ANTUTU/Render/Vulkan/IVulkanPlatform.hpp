#ifndef INTERFACE_VULKAN_PLATFORM_HPP
#define INTERFACE_VULKAN_PLATFORM_HPP

#include "VulkanCommon.hpp"
#include <vector>

namespace att
{
    class ANTUTU_API IVulkanPlatform
    {
    public:
        virtual ~IVulkanPlatform() = default;

        /**
         * @brief Get required instance extensions for the platform.
         * 
         * @return std::vector<const char*> List of required instance extensions.
         */
        virtual std::vector<const char*> GetRequiredInstanceExtensions() const = 0;

        virtual void createSurface(vk::Instance instance, VkSurfaceKHR* outSurface) const = 0;
    };
}

#endif // INTERFACE_VULKAN_PLATFORM_HPP