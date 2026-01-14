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
#include "ANTUTU/System/Logger.hpp"

#include <GLFW/glfw3.h>

/////////////////////////////////////////////////////////////////////////////////////
/// Implementation att::VulkanContext.
/////////////////////////////////////////////////////////////////////////////////////
namespace att
{
    ////////////////////////////////////////////////////////////////////////////////////////
    /// Constructor
    ////////////////////////////////////////////////////////////////////////////////////////

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
                                 uint32_t apiVersion,
                                 std::shared_ptr<System::Logger> logger
    ) : m_context(),
        m_instance(nullptr),
        m_logger(logger),
        m_debugMessenger(nullptr),
        m_surface(nullptr),
        m_physicalDevice(nullptr),
        m_device(nullptr),
        m_graphicsQueue(nullptr),
        m_presentQueue(nullptr)
    {
        // initialize members.
        m_queueIndices                                      = {};
        // initialize instance descriptor.
        m_instanceDescriptor.applicationName                = applicationName;
        m_instanceDescriptor.engineName                     = engineName;
        m_instanceDescriptor.applicationVersion             = applicationVersion;
        m_instanceDescriptor.engineVersion                  = engineVersion;
        m_instanceDescriptor.apiVersion                     = apiVersion;
        m_instanceDescriptor.enableValidationLayers         = enableValidationLayers;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    /// Destructor
    ////////////////////////////////////////////////////////////////////////////////////////

    /// @brief Destructor
    VulkanContext::~VulkanContext()
    {
        // Resources will be automatically cleaned up by vk::raii destructors.
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    /// void CreateInstance()
    ////////////////////////////////////////////////////////////////////////////////////////

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


    ////////////////////////////////////////////////////////////////////////////////////////
    /// void SetupdebugMessenger()
    ////////////////////////////////////////////////////////////////////////////////////////

    /// @brief Setup Debug Messenger
    /// @param none of parameters
    /// this function use a custom DebugMessageCallback,
    /// that permit listner can get log from vulkan core render or something else.
    void VulkanContext::SetupDebugMessenger()
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

        vk::DebugUtilsMessengerCreateInfoEXT            debugUtilsMessengerCreateInfoEXT{};
        debugUtilsMessengerCreateInfoEXT.messageSeverity        = severityFlags;
        debugUtilsMessengerCreateInfoEXT.messageType            = messageTypeFlags;
        debugUtilsMessengerCreateInfoEXT.pfnUserCallback = reinterpret_cast<vk::PFN_DebugUtilsMessengerCallbackEXT>(VulkanContext::DebugCallBack);
    
        debugUtilsMessengerCreateInfoEXT.pUserData       = this;

        return;
    }

    
    ////////////////////////////////////////////////////////////////////////////////////////
    /// bool CreateNativeSurface(void* windowHandle, void* instanceHandle)
    ////////////////////////////////////////////////////////////////////////////////////////

    /// @brief  Initialize Vulkan Device
    /// @param surface
    /// @param windowHandle pointer
    /// @param instanceHandle pointer
    /// @return boolean
    bool VulkanContext::CreateNativeSurface(void* windowHandle, void* instanceHandle)
    {
        try{
            // check windowsHandle
            if (windowHandle == nullptr)
            {
                m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_ERROR, "window is nullptr.");
                return false;
            }

            #if defined(ANTUTU_SYSTEM_WINDOWS)
                vk::Win32SurfaceCreateInfoKHR createInfo{};
                createInfo.hinstance            = static_cast<HINSTANCE> (instanceHandle);
                createInfo.hwnd                 = static_cast<HWND> (windowHandle);

                m_surface = vk::raii::SurfaceKHR(m_instance, createInfo);

            #elif defined(ANTUTU_SYSTEM_LINUX)
                if (instanceHandle == nullptr)
                {
                    return false;
                }
                vk::XlibSurfaceCreateInfoKHR createInfo{};
                createInfo.dpy                  = static_cast<Display*> (instanceHandle);
                createInfo.window               = reinterpret_cast<Window> (windowHandle);

                m_surface = vk::raii::SurfaceKHR(m_instance, createInfo);                       
            #else
                m_logger->WriteLog(System::ModuleName::CORE, System::LogLevel::ERROR, "unsupported platform.");
                return false;
            #endif

            return true;

        } 
        catch (const std::exception& e) {
            // return error
            m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_ERROR, e.what());
            return false;
        }
        return true;
    }



    ////////////////////////////////////////////////////////////////////////////////////////
    /// bool CreateSurface(GLFWwindow* window);
    ////////////////////////////////////////////////////////////////////////////////////////

    /// @brief Create Surface that use when you use GFLW for create windows.     
    /// @param GLFWwindow pointer
    /// @return 
    bool VulkanContext::CreateSurface(GLFWwindow* window)
    {
        try
        {
            if (window == nullptr)
            {
                m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_ERROR, "window is nullptr.");
                return false;
            }

            VkSurfaceKHR rawSurface;
            VkResult result = glfwCreateWindowSurface(*m_instance, window, nullptr, &rawSurface);

            if (result != VK_SUCCESS)
            {
                m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_ERROR, "cannot create glfw surface.");
                return false;
            }

            m_surface = vk::raii::SurfaceKHR(m_instance, rawSurface);
            return true;
        }
        catch(const std::exception& e) {
            // return error
            m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_ERROR, e.what());
            return false;
        }
        
        return true; 
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    /// bool PickPhysicalDevice();
    //////////////////////////////////////////////////////////////////////////////////////// 
    /// @brief Pick physical device
    /// @return 
    bool VulkanContext::PickPhysicalDevice()
    {
        return true;
    }


    ////////////////////////////////////////////////////////////////////////////////////////
    /// bool PickPhysicaldevice(vk::SurfaceKHR surface);
    ////////////////////////////////////////////////////////////////////////////////////////
    
    /// @brief
    /// @param surface
    /// @return
    bool VulkanContext::PickPhysicalDevice(vk::SurfaceKHR surface)
    {

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    /// QueueFamilyIndices FindQueueFamilies(const vk::raii::Physicaldevice& device);
    ////////////////////////////////////////////////////////////////////////////////////////

    /// @brief find queue families
    /// @param device 
    /// @return 
    QueueFamilyIndices VulkanContext::FindQueueFamilies(const vk::raii::PhysicalDevice& device)
    {
        QueueFamilyIndices indices;
        std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

        int i = 0;
        for (const auto& queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
            {
                indices.graphicsFamily = i;
            }


            // find the queue that support present to display on surface.
            // neeeded to check GPU support render on that surface or not.
            if (device.getSurfaceSupportKHR(i, *m_surface))
            {
                indices.presentFamily = i;
            }

            if (indices.isComplete())
            {
                break;
            }
            i++;
        }
        return indices;
    }

    /// @brief 
    /// @param surface 
    /// @return 
    bool VulkanContext::CreateLogicalDevice(vk::SurfaceKHR surface)
    {
        return false;
    }


    VKAPI_ATTR VkBool32 VKAPI_CALL VulkanContext::DebugCallBack(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData
    ) {
        auto* context = static_cast<VulkanContext*>(pUserData);
        if (!context || !pCallbackData || !pCallbackData->pMessage)
            return VK_FALSE;

        auto logger = context->getLogger();
        if (!logger)
            return VK_FALSE;

        System::LogLevel level = att::System::LogLevel::LOG_INFO;
        if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            level = System::LogLevel::LOG_ERROR;
        else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            level = System::LogLevel::LOG_WARNING;
        else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
            level = System::LogLevel::LOG_DEBUG;

        // get type of message 
        std::string prefix = "";
        if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) {
            prefix = "[Performance] ";
        }
        else if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) {
            prefix = "[Validation] ";
        }

        // final message data
        std::string msgBody = prefix + std::string(pCallbackData->pMessage);
        logger->WriteLog(System::ModuleName::MODULE_CORE, level, msgBody);

        return VK_FALSE;
    }

    int VulkanContext::RateDeviceSuitability(const vk::raii::PhysicalDevice& device)
    {
        int score = 0;
        // get property information and feature ( geometry shader)
        vk::PhysicalDeviceProperties deviceProperties       = device.getProperties();
        vk::PhysicalDeviceFeatures deviceFeatures           = device.getFeatures();

        // check geometry shader
        if (!deviceFeatures.geometryShader) {
            m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_WARNING, "There is no Geometry Shader.");
            return 0;
        }

        // check queue family indices
        QueueFamilyIndices indices = FindQueueFamilies(device);
        if (indices.isComplete() == false)
        {
            m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_WARNING, "There is no QueueFamilyIndices.");
            return 0;
        }

        // check if has extension supporting
        if (CheckDeviceExtensionSupport(device) == false)
        {
            m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_WARNING, "Device do not support extension.");
            return 0;
        }

        // plus score if physical device support render with GPU
        if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
        {
            score += 1000; // add score for physical device.
        }

        score += deviceProperties.limits.maxImageDimension2D;

        m_logger->WriteLog(System::ModuleName::MODULE_CORE, System::LogLevel::LOG_INFO, "get score for physical device sucessfully.");
        return score;
    }

    /// @brief 
    /// @param device 
    /// @return 
    bool VulkanContext::CheckDeviceExtensionSupport(const vk::raii::PhysicalDevice& device)
    {
        std::vector<vk::ExtensionProperties> availableExtensions = device.enumerateDeviceExtensionProperties();
        std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());

        for (const auto& extension : availableExtensions)
        {
            requiredExtensions.erase(extension.extensionName);
        }
        // if set is emtpty that mean we find all necesary extension.
        return requiredExtensions.empty();
    }

    /// @brief 
    /// @return 
    bool VulkanContext::CheckValidationLayerSupport()
    {
        return true;
    }
    
    
    /// @brief init full functional of vulkan context.
    /// using this function if you want create quickly vulkan context and fully.
    void VulkanContext::InitInstance()
    {
        // To be implemented.
        //CreateInstance();
    }

} // end att namespace