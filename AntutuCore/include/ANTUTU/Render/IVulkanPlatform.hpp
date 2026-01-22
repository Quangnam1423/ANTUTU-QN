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

#ifndef ANTUTU_VULKAN_PLATFORM_INTERFACE_HPP
#define ANTUTU_VULKAN_PLATFORM_INTERFACE_HPP

#include "ANTUTU/Config.hpp"

#include <cstring>
#include <vector>

#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#	include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif

namespace att
{
    struct ANTUTU_API VulkanPlatformInfo {
        std::vector<const char*> instanceExtensions;
        std::vector<const char*> validationLayers;
    };

    class IVulkanPlatform
    {
        virtual ~IVulkanPlatform() = default;

        virtual VulkanPlatformInfo GetVulkanInfo() const = 0;
        virtual VkSurfaceKHR CreateSurface(VkInstance instance) = 0;
    };

}

#endif