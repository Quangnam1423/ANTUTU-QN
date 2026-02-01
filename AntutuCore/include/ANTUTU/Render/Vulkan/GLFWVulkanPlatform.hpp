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
#ifndef ANTUTU_GLFW_VULKAN_PLATFORM_HPP
#define ANTUTU_GLFW_VULKAN_PLATFORM_HPP

#include "VulkanCommon.hpp"

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif

#include <GLFW/glfw3.h>

#include "IVulkanPlatform.hpp"

namespace att
{
    class ANTUTU_API GLFWVulkanPlatform : public IVulkanPlatform
    {
    public:
        GLFWVulkanPlatform() = default;
        virtual ~GLFWVulkanPlatform() = default;
        /**
         * @brief Get required instance extensions for the platform.
         * 
         * @return std::vector<const char*> List of required instance extensions.
         */
        std::vector<const char*> GetRequiredInstanceExtensions() const override;

        void createSurface(vk::Instance instance, VkSurfaceKHR* outSurface) const override;
    };
}

#endif // ANTUTU_GLFW_VULKAN_PLATFORM_HPP