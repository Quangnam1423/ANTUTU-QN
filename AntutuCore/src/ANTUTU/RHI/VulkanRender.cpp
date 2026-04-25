#include <ANTUTU/RHI/VulkanRender.hpp>

#include <map>
#include <set>
#include <vector>
#include <iostream>


namespace att::RHI
{
    bool VulkanRender::Initialize(const WindowHandle &windowHandle, uint32_t width, uint32_t height)
    {
        if (!CreateInstance(windowHandle)) {
            std::cerr << "Failed to create Vulkan instance." << std::endl;
            return false;
        }

        if (!CreateSurface(windowHandle)) {
            std::cerr << "Failed to create Vulkan surface." << std::endl;
            return false;
        }

        if (!PickPhysicalDevice()) {
            std::cerr << "Failed to pick a suitable physical device." << std::endl;
            return false;
        }

        if (!CreateLogicalDevice()) {
            std::cerr << "Failed to create logical device." << std::endl;
            return false;
        }

        if (!CreateSwapchain(width, height)) {
            std::cerr << "Failed to create swapchain." << std::endl;
            return false;
        }

        // Additional initialization like command buffers, pipelines, etc. would go here.

        return true;
    }

    std::vector<const char*> GetRequiredExtensions(std::vector<const char*> &additionalExtensions)
    {
        std::vector<const char*> result = additionalExtensions;

        
    }

    void VulkanRender::RenderFrame()
    {
    }

    void VulkanRender::Resize(uint32_t width, uint32_t height)
    {
    }

    void VulkanRender::Cleanup()
    {
    }

    bool VulkanRender::CreateInstance(const WindowHandle& handle)
    {
        if (enableValidationLayers && !CheckValidationLayerSupport()) {
            std::cerr << "Validation layers requested, but not available!" << std::endl;
            return false;
        }

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "ANTUTU Vulkan Renderer";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "ANTUTU Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Get required extensions based on the window system type.
        std::vector<const char*> extensions;
        // All platforms require the surface extension for creating surfaces.
        extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

        // Add platform-specific extensions for surface creation.
        switch (handle.systemType)
        {
            case WindowSystemType::WINDOWS:
            {
                extensions.push_back("VK_KHR_win32_surface");
                break;
            }
            case WindowSystemType::X11:
            {
                extensions.push_back("VK_KHR_xlib_surface");
                break;
            }
            case WindowSystemType::GLFW:
            {
                uint32_t glfwExtensionCount = 0;
                const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
                for (uint32_t i = 0; i < glfwExtensionCount; i++) {
                    extensions.push_back(glfwExtensions[i]);
                }
                break;
            }
            default:
                std::cerr << "Unsupported window system type!" << std::endl;
                return false;
        }
        // handle extensions and layers as needed, 
        // for now we will just create a basic instance with the required extensions 
        // for surface creation.
        if (enableValidationLayers) 
        {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enableValidationLayers)
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
        if (result != VK_SUCCESS) {
            std::cerr << "Failed to create Vulkan instance: " << result << std::endl;
            return false;
        }

        return true;
    }

    bool VulkanRender::CreateSurface(const WindowHandle &handle)
    {
        VkResult err;

        switch (handle.systemType) {
            case WindowSystemType::WINDOWS: 
            {
                VkWin32SurfaceCreateInfoKHR createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
                createInfo.hwnd = static_cast<HWND>(handle.win32.hwnd);
                createInfo.hinstance = static_cast<HINSTANCE>(handle.win32.hinstance);
                err = vkCreateWin32SurfaceKHR(m_instance, &createInfo, nullptr, &m_surface);
                break;
            }
            case WindowSystemType::X11:
                // Create X11 surface, for now we will focus on Windows and GLFW, 
                // so we can leave this unimplemented.
                break;
            case WindowSystemType::GLFW:
                err = glfwCreateWindowSurface(m_instance, 
                                                static_cast<GLFWwindow*>(handle.glfw.window), 
                                                nullptr, 
                                                &m_surface);
                break;
            default:
                return false;
        }
        return err == VK_SUCCESS;
    }


    bool VulkanRender::PickPhysicalDevice()
    {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

        if (deviceCount == 0)
        {
            std::cerr << "Failed to find GPUs with Vulkan support!" << std::endl;
            return false;
        }

        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());
        std::multimap<int, VkPhysicalDevice> candidates;

        for (const auto& device : devices)
        {
            int score = RateDeviceSuitability(device);
            candidates.insert({score, device});
        }

        if (candidates.rbegin()->first > 0)
        {
            m_physicalDevice = candidates.rbegin()->second;
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(m_physicalDevice, &properties);

            std::cout << "Selected GPU: " << properties.deviceName << " with score "
                        << candidates.rbegin()->first << std::endl;
        }
        else
        {
            std::cerr << "Failed to find a suitable GPU!" << std::endl;
            return false;
        }
        return true;
    }

    bool VulkanRender::CreateLogicalDevice()
    {
        QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);

        if (!indices.IsComplete())
        {
            std::cerr << "Failed to find required queue families!" << std::endl;
            return false;
        }

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {
            indices.graphicsFamily.value(),
            indices.presentFamily.value()
        };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeature{};
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeature;

        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };
        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();

        if (enableValidationLayers) 
        {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else 
        {
            createInfo.enabledLayerCount = 0;
        }

        if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
            std::cerr << "Failed to create logical device!" << std::endl;
            return false;
        }
        vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);

        return true;
    }

    bool VulkanRender::CreateSwapchain(uint32_t width, uint32_t height)
    {
        SwapChainSupportDetails swapChainSupport = QuerySwapChainSupport(m_physicalDevice);
        VkSurfaceFormatKHR surfaceFormat = ChooseSwapSurfaceFormat(swapChainSupport.formats);
        VkPresentModeKHR presentMode = ChooseSwapPresentMode(swapChainSupport.presentModes);
        VkExtent2D extent = ChooseSwapExtent(swapChainSupport.capabilities, width, height);

        uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

        if (swapChainSupport.capabilities.maxImageCount > 0 && 
            imageCount > swapChainSupport.capabilities.maxImageCount
        ) {
            imageCount = swapChainSupport.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        createInfo.surface = m_surface;
        createInfo.minImageCount = imageCount;
        createInfo.imageFormat = surfaceFormat.format;
        createInfo.imageColorSpace = surfaceFormat.colorSpace;
        createInfo.imageExtent = extent;
        createInfo.imageArrayLayers = 1;
        createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        QueueFamilyIndices indices = FindQueueFamilies(m_physicalDevice);
        uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        if (indices.graphicsFamily != indices.presentFamily) {
            createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            createInfo.queueFamilyIndexCount = 2;
            createInfo.pQueueFamilyIndices = queueFamilyIndices;
        } else {
            createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
        createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        createInfo.presentMode = presentMode;
        createInfo.clipped = VK_TRUE;
        createInfo.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
            std::cerr << "Failed to create swapchain!" << std::endl;
            return false;
        }

        m_swapchainImageFormat = surfaceFormat.format;
        m_swapchainExtent = extent;


        vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, nullptr);
        m_swapchainImages.resize(imageCount);
        vkGetSwapchainImagesKHR(m_device, m_swapchain, &imageCount, m_swapchainImages.data());

        m_swapchainImageViews.resize(m_swapchainImages.size());

        for (size_t i = 0; i < m_swapchainImages.size(); i++) {
            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = m_swapchainImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = m_swapchainImageFormat;
            viewInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(m_device, &viewInfo, nullptr, &m_swapchainImageViews[i]) != VK_SUCCESS) {
                std::cerr << "Failed to create image view!" << std::endl;
                return false;
            }
        }

        return true;
    }

    bool VulkanRender::CheckValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }


    // For now we will just return a dummy score, 
    // in a real implementation we would check for various features and properties 
    // of the device to determine how suitable it is for our needs.

    /**
     * TODO: Implement a proper scoring system based on device properties and features,
     * such as checking for discrete GPU, supported features, queue families, etc.
     * For example:
     * VkPhysicalDeviceProperties deviceProperties;
     * vkGetPhysicalDeviceProperties(device, &deviceProperties);
     * if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
     *   score += 1000;
     * }
     * 1. Graphics Queue vaf Present Queue support
     * 2. Device features (e.g. geometry shader, tessellation shader, etc
     * 3. Swapchain support (formats, present modes, etc.)
     * 4. present mode support (e.g. VK_PRESENT_MODE_MAILBOX_KHR is better than VK_PRESENT_MODE_FIFO_KHR)
     * 5. Memory and performance characteristics (e.g. dedicated video memory size)
     */
    int VulkanRender::RateDeviceSuitability(VkPhysicalDevice device)
    {
        int score = 0;
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

        switch (deviceProperties.deviceType)
        {
            case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
                score += 10000;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
                score += 1000;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
                score += 100;
                break;
            case VK_PHYSICAL_DEVICE_TYPE_CPU:
                score += 100;
                break;
            default:
                break;
        }

        score += deviceProperties.limits.maxImageDimension2D;

        if (deviceFeatures.geometryShader) 
        {
            score += 500;
        }
        else 
        {
            return 0;
        }

        return score;
    }


    QueueFamilyIndices VulkanRender::FindQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.IsComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    SwapChainSupportDetails VulkanRender::QuerySwapChainSupport(VkPhysicalDevice device)
    {
        SwapChainSupportDetails details;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);
        if (formatCount != 0)
        {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);
        if (presentModeCount != 0)
        {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    VkSurfaceFormatKHR VulkanRender::ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
    {
        for (const auto& availableFormat : availableFormats)
        {
            if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && 
                availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
            {
                return availableFormat;
            }
        }
        return availableFormats[0];
    }


    VkPresentModeKHR VulkanRender::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
    {
        for (const auto& availablePresentMode : availablePresentModes)
        {
            if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
            {
                return availablePresentMode;
            }
        }
        return VK_PRESENT_MODE_FIFO_KHR;
    }


    VkExtent2D VulkanRender::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t width, uint32_t height)
    {
        if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
        {
            return capabilities.currentExtent;
        }
        else 
        {
            VkExtent2D actualExtent = {width, height};

            actualExtent.width = std::clamp(actualExtent.width, 
                                            capabilities.minImageExtent.width, 
                                            capabilities.maxImageExtent.width);

            actualExtent.height = std::clamp(actualExtent.height, 
                                            capabilities.minImageExtent.height, 
                                            capabilities.maxImageExtent.height);

            return actualExtent;
        }
    }


};
