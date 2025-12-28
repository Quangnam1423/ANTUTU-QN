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

// =========================Antutu::VulkanInstance.hpp=========================

#ifndef ANTUTU_VULKANINSTANCE_HPP
#define ANTUTU_VULKANINSTANCE_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#ifdef NDEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false;
#endif


#include <vector>
#include <string>

namespace Antutu {
    /**
     * @class VulkanInstance
     * @brief A class that encapsulates a Vulkan instance.
     * This class handles the creation and destruction of a Vulkan instance,
     * including validation layers and required extensions.
     * @author Quangnam1423
     */
    class VulkanInstance {
    public:
        VulkanInstance(const std::string& appName, 
            const std::vector<const char*>& requiredExtensions, 
            bool enableValidationLayers);
            
        ~VulkanInstance();

        VulkanInstance(const VulkanInstance&) = delete;
        VulkanInstance& operator=(const VulkanInstance&) = delete;
        VulkanInstance(VulkanInstance&&) = delete;
        VulkanInstance& operator=(VulkanInstance&&) = delete;

        VkInstance GetInstance() const;
        
    private:
        void CreateInstance(const std::string& appName, 
            const std::vector<const char*>& requiredExtensions);

        std::vector<const char*> GetValidationLayers() const;

        bool CheckValidationLayerSupport() const;

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);
            
    private:
        VkInstance m_instance;
        VkDebugUtilsMessengerEXT m_debugMessenger;
        bool m_enableValidationLayers;
    };
}


#endif // ANTUTU_VULKANINSTANCE_HPP