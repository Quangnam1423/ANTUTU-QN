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

#include "ANTUTU/Render/Vulkan/VulkanSurface.hpp"


namespace att
{
    VulkanSurface::VulkanSurface(VkInstance instance, VkSurfaceKHR handle)
        : m_instance(instance), m_surface(handle)
    {
    }

    VulkanSurface::~VulkanSurface()
    {
        Destroy();
    }

    VulkanSurface::VulkanSurface(VulkanSurface&& other) noexcept
        : m_instance(other.m_instance), m_surface(other.m_surface)
    {
        other.m_surface = VK_NULL_HANDLE;
    }

    VulkanSurface& VulkanSurface::operator=(VulkanSurface&& other) noexcept
    {
        if (this != &other)
        {
            Destroy();
            m_instance = other.m_instance;
            m_surface = other.m_surface;
            other.m_surface = VK_NULL_HANDLE;
        }
        return *this;
    }

    VkSurfaceKHR VulkanSurface::GetHandle() const
    {
        return m_surface;
    }

    void VulkanSurface::Destroy()
    {
        if (m_surface != VK_NULL_HANDLE)
        {
            vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
            m_surface = VK_NULL_HANDLE;
        }
    }
} // namespace att