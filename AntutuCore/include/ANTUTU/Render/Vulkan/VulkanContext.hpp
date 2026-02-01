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

#include "VulkanCommon.hpp"
#include "VulkanExtensionManager.hpp"
#include "VulkanSurface.hpp"

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
#include <map>
#include <set>

// Forward declaration of GLFWwindow
struct GLFWwindow; 

namespace att
{
    namespace System {
        class Logger;
    }

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
    /// Swap Chain Support Details Structure
    ////////////////////////////////////////////////////////////////////////////
    struct ANTUTU_API SwapChainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

    ////////////////////////////////////////////////////////////////////////////
    /// Queue Family Indices Structure
    ////////////////////////////////////////////////////////////////////////////
    struct ANTUTU_API VulkanInstanceDescriptor
    {
        const char* applicationName;
        uint32_t applicationVersion ;

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
         * @brief Constructor.
         * 
         * @param applicationName Name of the application.
         * @param engineName Name of the engine.
         * @param applicationVersion Version of the application.
         * @param engineVersion Version of the engine.
         * @param apiVersion Vulkan API version.
         * @param logger object to get log from vulkan core.
         */
        VulkanContext(const char* applicationName                   = "Antutu Vulkan Engine",
                      const char* engineName                        = "No Engine",
                      uint32_t applicationVersion                   = VK_MAKE_VERSION(ANTUTU_VERSION_MAJOR, 
                                                                        ANTUTU_VERSION_MINOR,   
                                                                        ANTUTU_VERSION_PATCH),
                      uint32_t engineVersion                        = VK_MAKE_VERSION(1, 0, 0),
                      uint32_t apiVersion                           = VK_API_VERSION_1_2,
                      std::shared_ptr<System::Logger> logger        = nullptr);

                      
        VulkanContext(const char* applicationName,
                      const char* engineName,
                      uint32_t applicationVersion,
                      uint32_t apiVersion,
                      bool enableValidation
        );

        // /**
        //  * @brief Constructor that automatically create Logger.
        //  * 
        //  * @param applicationName Name of the application.
        //  * @param engineName Name of the engine.
        //  * @param applicationVersion Version of the application.
        //  * @param engineVersion Version of the engine.
        //  * @param apiVersion Vulkan API version.
        //  */
        // VulkanContext(const char* applicationName           = "Antutu Vulkan Engine",
        //               const char* engineName                = "No Engine",
        //               uint32_t applicationVersion           = VK_MAKE_VERSION(ANTUTU_VERSION_MAJOR, 
        //                                                            ANTUTU_VERSION_MINOR,   
        //                                                            ANTUTU_VERSION_PATCH),
        //               uint32_t engineVersion                = VK_MAKE_VERSION(1, 0, 0),
        //               uint32_t apiVersion                   = VK_API_VERSION_1_2);

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
        void SetupDebugMessenger();



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

        bool PickPhysicalDevice();
        bool PickPhysicalDevice(vk::SurfaceKHR surface);
        QueueFamilyIndices FindQueueFamilies(const vk::raii::PhysicalDevice& device);
        SwapChainSupportDetails QuerySwapChainSupport(vk::PhysicalDevice device, vk::SurfaceKHR surface);

        bool CreateLogicalDevice(vk::SurfaceKHR surface);


        ////////////////////////////////////////////////////////////////////////////////////////////
        /// Getters
        ////////////////////////////////////////////////////////////////////////////////////////////
        const vk::raii::Instance& GetInstance() const { return m_instance; }
        const vk::raii::PhysicalDevice& GetPhysicalDevice() const { return m_physicalDevice; }
        const vk::raii::Device& GetDevice() const { return m_device; }
        const vk::raii::Queue& GetGraphicsQueue() const { return m_graphicsQueue; }
        const vk::raii::Queue& GetPresentQueue() const { return m_presentQueue; }
        const std::shared_ptr<System::Logger>& getLogger() const { return m_logger; }
        const vk::raii::CommandPool& GetCommandPool() const {return m_commandPool; }

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// Setters
        ////////////////////////////////////////////////////////////////////////////////////////////
        void SetLogger(std::shared_ptr<System::Logger> logger) {m_logger = logger; }
        uint32_t GetGraphicsQueueFamilyIndex() const { return m_queueIndices.graphicsFamily.value(); }
        void AddInstanceExtension(const char* extensionName);
        void AddInstanceLayer(const char* layerName);
        void SetInstanceExtensions(const std::vector<const char*>& extensions);

        ////////////////////////////////////////////////////////////////////////////////////////////
        /// helper functions public
        ////////////////////////////////////////////////////////////////////////////////////////////
        vk::raii::CommandBuffer BeginSingleTimeCommands();
        void EndSingleTimeCommand(vk::raii::CommandBuffer& commandBuffer);
    private:
        ////////////////////////////////////////////////////////////////////////////////////////////
        /// static function to setup sign of Vulkan
        ////////////////////////////////////////////////////////////////////////////////////////////
        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallBack(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        );


        ////////////////////////////////////////////////////////////////////////////////////////////
        /// helper functions
        ////////////////////////////////////////////////////////////////////////////////////////////
        int RateDeviceSuitability(const vk::raii::PhysicalDevice& device);
        bool CheckDeviceExtensionSupport(const vk::raii::PhysicalDevice& device);
        void CreateCommandPool();
        bool CheckValidationLayerSupport();
        //void PickPhysicalDevice(vk::SurfaceKHR surface);
        //void CreateLogicalDevice(vk::SurfaceKHR surface);


    private:
        
        VulkanInstanceDescriptor                        m_instanceDescriptor;      // descriptor for instance creation
        vk::raii::Context                               m_context;                 // vulkan context
        vk::raii::Instance                              m_instance;                // vulkan instance
        std::shared_ptr<System::Logger>                 m_logger;                  // logger for get log
        vk::raii::DebugUtilsMessengerEXT                m_debugMessenger;          // debug messenger
        vk::raii::SurfaceKHR                            m_surface;                 // vulkan surface
        vk::raii::PhysicalDevice                        m_physicalDevice;          // physical device
        vk::raii::Device                                m_device;                  // logical device
        vk::raii::Queue                                 m_graphicsQueue;           // graphics queue
        vk::raii::Queue                                 m_presentQueue;            // graphics and present queues
        vk::raii::CommandPool                           m_commandPool;             // command pool
        QueueFamilyIndices                              m_queueIndices;            // indices of queue families

        // test.
        const std::vector<const char*>                  m_deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
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
 * using CreateNativeSurface() when you want to create a native surface. Supported linux and windows win32API.
 */