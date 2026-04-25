#ifndef ANTUTU_RHI_VULKAN_SURFACE_HPP
#define ANTUTU_RHI_VULKAN_SURFACE_HPP

#include <ANTUTU/VulkanCommon.hpp>

namespace att::RHI
{
    class ANTUTU_API VulkanSurface
    {
    public:

        VkSurfaceKHR getSurface() const;

    private:
        VkSurfaceKHR m_surface;
    };
}

#endif // ANTUTU_RHI_VULKAN_SURFACE_HPP