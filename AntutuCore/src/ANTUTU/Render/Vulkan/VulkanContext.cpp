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

#include "ANTUTU/Render/Vulkan/VulkanContext.hpp"

#include <GLFW/glfw3.h>

/////////////////////////////////////////////////////////////////////////////////////
/// Implementation att::VulkanContext.
/////////////////////////////////////////////////////////////////////////////////////
namespace att
{
    /// @brief Constructor
    /// @param applicationName 
    /// @param engineName 
    /// @param applicationVersion 
    /// @param engineVersion 
    /// @param apiVersion 
    VulkanContext::VulkanContext(const char* applicationName,
                                 const char* engineName,
                                 uint32_t applicationVersion,
                                 uint32_t engineVersion,
                                 uint32_t apiVersion
    ) : m_context(),
        m_instance(nullptr),
        m_debugMessenger(nullptr),
        m_physicalDevice(nullptr),
        m_device(nullptr),
        m_graphicsQueue(nullptr),
        m_presentQueue(nullptr)
    {
        // initialize members.
        m_queueIndices = {};
        // initialize instance descriptor.
        m_instanceDescriptor.applicationName = applicationName;
        m_instanceDescriptor.engineName = engineName;
        m_instanceDescriptor.applicationVersion = applicationVersion;
        m_instanceDescriptor.engineVersion = engineVersion;
        m_instanceDescriptor.apiVersion = apiVersion;
        m_instanceDescriptor.enableValidationLayers = enableValidationLayers;
    }

    /// @brief Destructor
    VulkanContext::~VulkanContext()
    {
        // Resources will be automatically cleaned up by vk::raii destructors.
    }

    /// @brief 
    /// @param extensions 
    void VulkanContext::CreateInstance()
    {
        // Application Info.
        vk::ApplicationInfo appInfo{};
        appInfo.pApplicationName                    = "Antutu Vulkan Engine";
        appInfo.applicationVersion                  = VK_MAKE_VERSION(ANTUTU_VERSION_MAJOR, 
                                                                        ANTUTU_VERSION_MINOR,   
                                                                        ANTUTU_VERSION_PATCH
                                                            );
        appInfo.pEngineName                         = "No Engine";
        appInfo.engineVersion                       = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion                          = VK_API_VERSION_1_2;

        // Get required layers.
        std::vector<char const*> requiredLayers;
        if (m_instanceDescriptor.enableValidationLayers)
        {
            requiredLayers.assign(m_instanceDescriptor.layers.begin(), m_instanceDescriptor.layers.end());
        }
        auto layerProperties = m_context.enumerateInstanceLayerProperties();
        for (const char* requiredName : requiredLayers)
        {
            auto it = std::find_if(layerProperties.begin(), layerProperties.end(),
                [requiredName](const vk::LayerProperties& layerProp)
                {
                    return std::strcmp(layerProp.layerName, requiredName) == 0;
                });
            if (it == layerProperties.end())
            {
                throw std::runtime_error("Required validation layer not found: " + std::string(requiredName));
            }
        }

        // get the required extensions.
        auto requiredExtensions = m_instanceDescriptor.extensions;

        // Check if the required extensions are supported by the Vulkan implementation.
        auto extensionProperties = m_context.enumerateInstanceExtensionProperties();
        for (auto const $requiredExtension : requiredExtensions)
        {
            bool found = false;
            for (const auto& prop : extensionProperties)
            {
                if (strcmp(prop.extensionName, $requiredExtension) == 0)
                {
                    found = true;
                    break;
                }
            }

            // If a required extension is not found, throw an error.
            if(found == false)
            {
                throw std::runtime_error("Required extension not found: " + std::string($requiredExtension));
            }
        }

        // Instance Create Info.
        vk::InstanceCreateInfo createInfo{};
        createInfo.pApplicationInfo                 = &appInfo;
        createInfo.enabledLayerCount                = static_cast<uint32_t>(requiredLayers.size());
        createInfo.ppEnabledLayerNames              = requiredLayers.data();
        createInfo.enabledExtensionCount            = static_cast<uint32_t>(m_instanceDescriptor.extensions.size());
        createInfo.ppEnabledExtensionNames          = m_instanceDescriptor.extensions.data();
        m_instance = vk::raii::Instance(m_context, createInfo);
    }

    /// @brief Setup Debug Messenger
    /// @param none of parameters
    /// this function use a custom DebugMessageCallback,
    /// that permit listner can get log from vulkan core render or something else.
    void VulkanContext::setupDebugMessenger()
    {
        // check if debug mode turn on
        if (m_instanceDescriptor.enableValidationLayers == false)
        {
            return;
        }

        // if debug mode is on, then create message debug and callback for listener
        vk::DebugUtilsMessageSeverityFlagsEXT           severityFlags(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
                                                                | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning 
                                                                | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError );

        vk::DebugUtilsMessageTypeFlagsEXT               messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
                                                                | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance
                                                                | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);

        // vk::DebugUtilsMessengerCreateInfoEXT            debugUtilsMessengerCreateInfoEXT{
        //                                                     .messageSeverity = severityFlags,
        //                                                 };
    }

    /// @brief  Initialize Vulkan Device
    /// @param surface
    /// @param windowHandle pointer
    /// @param instanceHandle pointer
    /// @return 
    bool CreateNativeSurface(void* windowHandle, void* instanceHandle)
    {
        return false;
    }

    /// @brief      
    /// @param GLFWwindow pointer
    /// @return 
    bool VulkanContext::CreateSurface(GLFWwindow* window)
    {
        return false;
    }

    void VulkanContext::InitInstance()
    {
        // To be implemented.
        //CreateInstance();
    }
}