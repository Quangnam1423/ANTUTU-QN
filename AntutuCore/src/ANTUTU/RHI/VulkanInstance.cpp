#include <ANTUTU/RHI/VulkanInstance.hpp>

namespace att::RHI
{
    VulkanInstance::~VulkanInstance()
    {
        Destroy();
        std::cout << "Vulkan instance destroyed." << std::endl;
    }

    bool VulkanInstance::Initialize(const PlatformInfo::VulkanInstanceConfig& config)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = config.appName;
        appInfo.applicationVersion = config.appVer;
        appInfo.pEngineName = config.engineName;
        appInfo.engineVersion = config.engineVer;
        appInfo.apiVersion = config.apiVer;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(config.exts.size());
        createInfo.ppEnabledExtensionNames = config.exts.data();

        if (config.isEnableValidationLayers) 
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(config.layers.size());
            createInfo.ppEnabledLayerNames = config.layers.data();
        } 
        else 
        {
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) 
        {
            throw std::runtime_error("Failed to create Vulkan instance");
            return false;
        }
        return true;
    }

    void VulkanInstance::Destroy()
    {
        if (m_instance != VK_NULL_HANDLE) 
        {
            vkDestroyInstance(m_instance, nullptr);
            m_instance = VK_NULL_HANDLE;
        }
    }

    bool VulkanInstance::checkValidationLayerSupport(const std::vector<const char*>& layers)
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : layers) 
        {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) 
            {
                if (strcmp(layerName, layerProperties.layerName) == 0) 
                {
                    layerFound = true;
                    break;
                }
            }
            if (!layerFound) 
            {
                return false;
            }
        }
        return true;
    }


    // Set up the debug messenger if validation layers are enabled
    // This is where you would fill in VkDebugUtilsMessengerCreateInfoEXT
    // and call vkCreateDebugUtilsMessengerEXT
    void VulkanInstance::setupDebugMessenger()
    {

    }
};