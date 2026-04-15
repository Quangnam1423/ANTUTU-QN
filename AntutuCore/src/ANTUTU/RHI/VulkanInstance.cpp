#include <ANTUTU/RHI/VulkanInstance.hpp>

namespace att::RHI
{
    void VulkanInstance::Initialize(const InstanceDescriptor& descriptor, SurfaceCreateProc surfaceCreateProc)
    {
        this->createInstance(descriptor);
        this->setupDebugMessenger();
        
        if (surfaceCreateProc) 
        {
            m_surface = surfaceCreateProc(m_instance);
        }
        else 
        {
            throw std::runtime_error("Surface creation procedure is not provided.");
        }
    }

    // Create Vulkan instance using the provided descriptor
    // This is where you would fill in VkApplicationInfo and VkInstanceCreateInfo
    // and call vkCreateInstance
    void VulkanInstance::createInstance(const InstanceDescriptor& descriptor)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = descriptor.applicationName;
        appInfo.applicationVersion = descriptor.applicationVersion;
        appInfo.pEngineName = descriptor.engineName;
        appInfo.engineVersion = descriptor.engineVersion;
        appInfo.apiVersion = descriptor.apiVersion;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(descriptor.extensions.size());
        createInfo.ppEnabledExtensionNames = descriptor.extensions.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(descriptor.layers.size());
        createInfo.ppEnabledLayerNames = descriptor.layers.data();
        createInfo.flags = 0; // Optional flags can be set here

        if (descriptor.isEnableValidationLayers) 
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(descriptor.layers.size());
            createInfo.ppEnabledLayerNames = descriptor.layers.data();
        } 
        else 
        {
            createInfo.enabledLayerCount = 0;
            createInfo.ppEnabledLayerNames = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) 
        {
            throw std::runtime_error("Failed to create Vulkan instance");
        }
    }

    // Set up the debug messenger if validation layers are enabled
    // This is where you would fill in VkDebugUtilsMessengerCreateInfoEXT
    // and call vkCreateDebugUtilsMessengerEXT
    void VulkanInstance::setupDebugMessenger()
    {

    }
};