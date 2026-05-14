/*
 * ISurfaceProvider.hpp
 *
 *  Created on: 4/16/2026
 *      Author: Quangnam1423
 * 
 *  Description: This file defines the ISurfaceProvider interface, 
 * which provides an abstraction for creating Vulkan surfaces.
 * This interface as a contract for any platform-specific surface provider implementation,
 * allowing the rendering engine to create Vulkan surfaces 
 * without being tightly coupled to platform-specific details.
 */

#ifndef ANTUTU_RHI_ISURFACE_PROVIDER_HPP
#define ANTUTU_RHI_ISURFACE_PROVIDER_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <vector>

namespace att::RHI
{
    class ISurfaceProvider
    {
    public:
        virtual ~ISurfaceProvider() = default;

        virtual VkSurfaceKHR* CreateSurface(VkInstance instance) const = 0;

		virtual std::vector<const char*> GetRequiredExtensions() const = 0;
    };
}

#endif // ANTUTU_RHI_ISURFACE_PROVIDER_HPP