#include <ANTUTU/RHI/VulkanRender.hpp>

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
        std::vector<const char*> extensions;
        extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);

        switch (handle.systemType)
        {
            case WindowSystemType::WINDOWS:
                extensions.push_back("VK_KHR_win32_surface");
                break;
            case WindowSystemType::X11:
                extensions.push_back("VK_KHR_xlib_surface");
                break;
            case WindowSystemType::GLFW:
                uint32_t glfwExtensionCount = 0;
                const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
                for (uint32_t i = 0; i < glfwExtensionCount; i++) {
                    extensions.push_back(glfwExtensions[i]);
                }
                break;
        }
        // handle extensions and layers as needed, 
        // for now we will just create a basic instance with the required extensions 
        // for surface creation.

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
        return false;
    }

    bool VulkanRender::CreateLogicalDevice()
    {
        return false;
    }

    bool VulkanRender::CreateSwapchain(uint32_t width, uint32_t height)
    {
        return false;
    }
};
