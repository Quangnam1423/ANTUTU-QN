#ifndef ANTUTU_RHI_VULKAN_CONTEXT_HPP
#define ANTUTU_RHI_VULKAN_CONTEXT_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <ANTUTU/RHI/VulkanContext.hpp>
#include <ANTUTU/RHI/InstanceDescriptor.hpp>
#include <ANTUTU/RHI/ISurfaceProvider.hpp>
#include <ANTUTU/PlatformInfo/VulkanInstanceConfig.h>

#include <vector>
#include <string>
#include <optional>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <functional>


namespace att::RHI
{
	using CustomLogCallback = std::function<void(VkDebugUtilsMessageSeverityFlagBitsEXT severity, const std::string& message)>;

	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData)
    {
        auto* externalCallback = reinterpret_cast<CustomLogCallback*>(pUserData);
        if (externalCallback) {
            (*externalCallback)(messageSeverity, pCallbackData->pMessage);
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
            void setupDebugMessenger();
            void customDebugHandler(VkDebugUtilsMessageSeverityFlagBitsEXT,
                                    VkDebugUtilsMessageTypeFlagBitsEXT,
                                    const VkDebugUtilsMessengerCallbackDataEXT*);

        private:

            VkInstance m_instance = VK_NULL_HANDLE;
            VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;
    };
};

#endif // ANTUTU_RHI_VULKAN_CONTEXT_HPP