#ifndef ANTUTU_RHI_VULKAN_RENDER_HPP
#define ANTUTU_RHI_VULKAN_RENDER_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <ANTUTU/RHI/VulkanSurface.hpp>
#include <ANTUTU/RHI/WindowHandle.h>
#include <GLFW/glfw3.h>

namespace att::RHI
{
    class ANTUTU_API VulkanRender
    {
    public:
        VulkanRender() = default;
        ~VulkanRender() = default;

        VulkanRender(const VulkanRender&) = delete;
        VulkanRender& operator=(const VulkanRender&) = delete;

        bool Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height);

        void RenderFrame();

        void Resize(uint32_t width, uint32_t height);

        void Cleanup();

    private:
        // Add necessary private members for rendering, such as command buffers, pipelines, etc.
        bool CreateInstance(const WindowHandle& handle);
        bool CreateSurface(const WindowHandle& handle);
        bool PickPhysicalDevice();
        bool CreateLogicalDevice();
        bool CreateSwapchain(uint32_t width, uint32_t height);
    
    private:
        VkInstance m_instance{VK_NULL_HANDLE};
        VkSurfaceKHR m_surface{VK_NULL_HANDLE};
        VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
        VkDevice m_device{VK_NULL_HANDLE};
        VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
        // Other Vulkan objects like command buffers, pipelines, etc.
    };
};

#endif // ANTUTU_RHI_VULKAN_RENDER_HPP