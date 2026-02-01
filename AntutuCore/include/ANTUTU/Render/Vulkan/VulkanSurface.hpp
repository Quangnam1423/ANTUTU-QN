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

#ifndef ANTUTU_VULKAN_SURFACE_HPP
#define ANTUTU_VULKAN_SURFACE_HPP

#include "VulkanCommon.hpp"

namespace att
{
    namespace System {
        class Logger;
    }

    class ANTUTU_API VulkanSurface
    {
    public:
        VulkanSurface(VkInstance instance, VkSurfaceKHR handle);
        ~VulkanSurface();

        VulkanSurface(const VulkanSurface&) = delete;
        VulkanSurface& operator=(const VulkanSurface&) = delete;
        VulkanSurface(VulkanSurface&& other) noexcept;
        VulkanSurface& operator=(VulkanSurface&& other) noexcept;

        VkSurfaceKHR GetHandle() const;

    private:
        void Destroy();
        
    private:
        VkInstance              m_instance;
        VkSurfaceKHR           m_surface;
    };
}

#endif // ANTUTU_VULKAN_SURFACE_HPP