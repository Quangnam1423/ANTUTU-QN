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


#ifndef ANTUTU_VULKAN_CONTEXT_HPP
#define ANTUTU_VULKAN_CONTEXT_HPP

#include "ANTUTU/Config.hpp"

// Standard Library Includes
#include <string>
#include <optional>
#include <algorithm>
#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <fstream>  
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#if defined(ANTUTU_SYSTEM_WINDOWS)
    #define VK_USE_PLATFORM_WIN32_KHR // for Windows
#endif


#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
    #include <vulkan/vulkan_raii.hpp>
#else
    import vulkan_hpp;
#endif

const std::vector<char const*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = true;
#else
    const bool enableValidationLayers = false; 
#endif

// Forward declaration of GLFWwindow
class GLFWwindow; 

namespace att
{
    ////////////////////////////////////////////////////////////////////////////
    /// Queue Family Indices Structure
    ////////////////////////////////////////////////////////////////////////////
    struct ANTUTU_API QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        bool isComplete()
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Queue Family Indices Structure
    ////////////////////////////////////////////////////////////////////////////
    struct ANTUTU_API VulkanInstanceDescriptor
    {
        const char* applicationName;
        uint32_t applicationVersion;

        const char* engineName;
        uint32_t engineVersion;

        uint32_t apiVersion;

        bool enableValidationLayers;

        std::vector<const char*> layers;
        std::vector<const char*> extensions;
    };

    /////////////////////////////////////////////////////////////////////////////
    /// Vulkan Context Class
    /////////////////////////////////////////////////////////////////////////////
    class ANTUTU_API VulkanContext
    {
    public:
        /**
         * @brief Constructor
         * 
         * @param applicationName Name of the application
         * @param engineName Name of the engine
         * @param applicationVersion Version of the application
         * @param engineVersion Version of the engine
         * @param apiVersion Vulkan API version
         */
        VulkanContext(const char* applicationName = "Antutu Vulkan Engine",
                      const char* engineName = "No Engine",
                      uint32_t applicationVersion = VK_MAKE_VERSION(ANTUTU_VERSION_MAJOR, 
                                                                   ANTUTU_VERSION_MINOR,   
                                                                   ANTUTU_VERSION_PATCH),
                      uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0),
                      uint32_t apiVersion = VK_API_VERSION_1_2);

        /**
         * @brief Destructor
         * 
         */
        ~VulkanContext();

        /**
         * @brief Initialize Vulkan Instance and Device
         * 
         * @param extensions List of required extensions
         * @param enableValidationLayers Enable validation layers
         */
        void InitInstance();

        /**
         * @brief Create Vulkan Instance
         * 
         */
        void CreateInstance();

        /**
         * @brief Setup Debug Messenger
         * 
         */
        void setupDebugMessenger();



        /**
         * @brief Initialize Vulkan Device
         * 
         * @param surface Vulkan Surface
         */
        void InitDevice(vk::SurfaceKHR surface);

        /**
         * @brief Create a Vulkan surface
         * @param windowHandle Native window handle
         * @param instanceHandle Native instance handle (optional)
         * @return vk::raii::SurfaceKHR Vulkan surface
         */
        bool CreateNativeSurface(void* windowHandle, void* instanceHandle = nullptr);                

        /**
        * @brief Create a Vulkan surface
        * @return vk::SurfaceKHR Vulkan surface
        */  
        bool CreateSurface(GLFWwindow* window);

        bool PickPhysicalDevice(vk::SurfaceKHR surface);
        bool CreateLogicalDevice(vk::SurfaceKHR surface);


        // Getters
        const vk::raii::Instance& GetInstance() const { return m_instance; }
        const vk::raii::PhysicalDevice& GetPhysicalDevice() const { return m_physicalDevice; }
        const vk::raii::Device& GetDevice() const { return m_device; }
        const vk::raii::Queue& GetGraphicsQueue() const { return m_graphicsQueue; }
        const vk::raii::Queue& GetPresentQueue() const { return m_presentQueue; }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// 
        ///
        ////////////////////////////////////////////////////////////////////////////////////////////
        uint32_t GetGraphicsQueueFamilyIndex() const { return m_queueIndices.graphicsFamily.value(); }
    private:
        bool CheckValidationLayerSupport();
        //void PickPhysicalDevice(vk::SurfaceKHR surface);
        //void CreateLogicalDevice(vk::SurfaceKHR surface);
        QueueFamilyIndices FindQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface);


    private:
        vk::raii::Context                               m_context;                 // vulkan context
        vk::raii::Instance                              m_instance;                // vulkan instance
        vk::raii::DebugUtilsMessengerEXT                m_debugMessenger;          // debug messenger
        vk::raii::PhysicalDevice                        m_physicalDevice;          // physical device
        vk::raii::Device                                m_device;                  // logical device
        vk::raii::Queue                                 m_graphicsQueue;           // graphics queue
        vk::raii::Queue                                 m_presentQueue;            // graphics and present queues
        QueueFamilyIndices                              m_queueIndices;            // indices of queue families        
        VulkanInstanceDescriptor                        m_instanceDescriptor;      // descriptor for instance creation
    };
}

#endif // ANTUTU_VULKAN_CONTEXT_HPP

/**
 * @file VulkanContext.cpp
 * @brief Implementation of the VulkanContext class.
 * @author Quangnam1423
 * @date 2025
 * 
 * needed to specify extension and validation layers during instance creation.
 * for example, enabling validation layers for debugging purposes.
 * 
 * Example:
 * std::vector<const char*> getRequiredExtensions()
 * {
 *  uint32_t glfwExtensionCount = 0;
 *  auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
 *  
 *  /// Create a vector to hold the required extensions
 *  std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
 *  if (enableValidationLayers) 
 *  {
 *     extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
 *  }
 *  return extensions;
*  }
 */