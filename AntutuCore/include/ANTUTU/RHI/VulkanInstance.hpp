#ifndef ANTUTU_RHI_VULKAN_CONTEXT_HPP
#define ANTUTU_RHI_VULKAN_CONTEXT_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <ANTUTU/RHI/VulkanContext.hpp>
#include <ANTUTU/RHI/InstanceDescriptor.hpp>
#include <ANTUTU/RHI/ISurfaceProvider.hpp>
#include <ANTUTU/PlatformInfo/VulkanInstanceConfig.h>
#include <Common/Logger/LogManager.h>

#include <vector>
#include <string>
#include <optional>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <functional>


namespace att::RHI
{

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        std::string typeStr = "";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) typeStr = "[General] ";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) typeStr = "[Validation] ";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) typeStr = "[Performance] ";

        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            LOG_ERROR("Vulkan Error: {0}{1}", typeStr, pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            LOG_WARN("Vulkan Warning: {0}{1}", typeStr, pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            LOG_INFO("Vulkan Info: {0}{1}", typeStr, pCallbackData->pMessage);
        }
        else {
            LOG_TRACE("Vulkan Trace: {0}{1}", typeStr, pCallbackData->pMessage);
        }

        return VK_FALSE;
    }

    class ANTUTU_API VulkanInstance {
        public:
            VulkanInstance() = default;

            ~VulkanInstance();    

            VulkanInstance(const VulkanInstance&) = delete;

            VulkanInstance& operator=(const VulkanInstance&) = delete;
        public:
            bool Initialize(const PlatformInfo::VulkanInstanceConfig& config);

            void Destroy();

            // getter and setter for Vulkan instance and debug messenger
        public: 
            VkInstance GetInstance() const { return m_instance; }

             // Add methods to query instance properties, enumerate physical devices, etc.
             // For example:
        private:
            bool checkValidationLayerSupport(const std::vector<const char*>& layers);

			void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

			VkResult CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* createInfo, 
                                                        const VkAllocationCallbacks* allocator, 
                                                        VkDebugUtilsMessengerEXT* debugMessenger);

			void DestroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT debugMessenger, 
                                                const VkAllocationCallbacks* allocator);
		// attributes
        private:
            VkInstance m_instance = VK_NULL_HANDLE;
            VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
    };
};

#endif // ANTUTU_RHI_VULKAN_CONTEXT_HPP