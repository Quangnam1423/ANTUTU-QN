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

        std::vector<const char*> extensions = config.exts;
        if constexpr (att::Config::EnableValidationLayers)
        {
            if (std::find(extensions.begin(), extensions.end(), VK_EXT_DEBUG_UTILS_EXTENSION_NAME) == extensions.end()) 
            {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        // Enable validation layers if in debug mode
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if constexpr (att::Config::EnableValidationLayers) 
        {
            if (!checkValidationLayerSupport(att::Config::validationLayers))
            {
                throw std::runtime_error("Validation layers requested, but not available!");
                return false;
            }
            createInfo.enabledLayerCount = static_cast<uint32_t>(att::Config::validationLayers.size());
            createInfo.ppEnabledLayerNames = att::Config::validationLayers.data();

			PopulateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
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

		// create debug messenger if validation layers are enabled
        if constexpr (att::Config::EnableValidationLayers)
        {
            if (CreateDebugUtilsMessengerEXT(&debugCreateInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) 
            {
                throw std::runtime_error("Failed to set up debug messenger!");
                return false;
			}
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

    void VulkanInstance::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
    {
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

        createInfo.pfnUserCallback = DebugCallback;

        createInfo.pUserData = nullptr;
	}

    VkResult VulkanInstance::CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* createInfo,
        const VkAllocationCallbacks* allocator,
        VkDebugUtilsMessengerEXT* debugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(m_instance, createInfo, allocator, debugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void VulkanInstance::DestroyDebugUtilsMessengerEXT(VkDebugUtilsMessengerEXT debugMessenger,
        const VkAllocationCallbacks* allocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(m_instance, debugMessenger, allocator);
        }
    }
};