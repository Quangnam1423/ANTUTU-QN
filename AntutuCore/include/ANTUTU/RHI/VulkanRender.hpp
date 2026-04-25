#ifndef ANTUTU_RHI_VULKAN_RENDER_HPP
#define ANTUTU_RHI_VULKAN_RENDER_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <ANTUTU/PlatformInfo/VulkanSurface.h>
#include <ANTUTU/RHI/WindowHandle.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

namespace att::RHI
{
    struct ANTUTU_API QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool IsComplete() const
        {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct ANTUTU_API SwapChainSupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct ANTUTU_API VulkanInitInfo
    {
        const char* applicationName;
        uint32_t applicationVersion;
        const char* engineName;
        uint32_t engineVersion;
        uint32_t apiVersion;
        std::vector<const char*> extensions;
        std::vector<const char*> layers;
    };

    class ANTUTU_API VulkanRender
    {
    public:
        VulkanRender() = default;
        ~VulkanRender() = default;

        VulkanRender(const VulkanRender&) = delete;
        VulkanRender& operator=(const VulkanRender&) = delete;

        bool Initialize(const WindowHandle& windowHandle, uint32_t width, uint32_t height);
        std::vector<const char*> GetRequiredExtensions(std::vector<const char*> &additionalExtensions);

        void RenderFrame();

        void Resize(uint32_t width, uint32_t height);

        void Cleanup();

    private:
        // Add necessary private members for rendering, 
        // such as command buffers, pipelines, etc.
        bool CreateInstance(const WindowHandle& handle);
        bool CreateSurface(const WindowHandle& handle);
        bool PickPhysicalDevice();
        bool CreateLogicalDevice();
        bool CreateSwapchain(uint32_t width, uint32_t height);
        bool CheckValidationLayerSupport();
        int RateDeviceSuitability(VkPhysicalDevice device);
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
        VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, uint32_t width, uint32_t height);
    
    private:
        VkInstance m_instance{VK_NULL_HANDLE};
        VkSurfaceKHR m_surface{VK_NULL_HANDLE};
        VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
        VkDevice m_device{VK_NULL_HANDLE};
        VkQueue m_graphicsQueue{VK_NULL_HANDLE};
        VkQueue m_presentQueue{VK_NULL_HANDLE};
        VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
        VkFormat m_swapchainImageFormat;
        VkExtent2D m_swapchainExtent;
        std::vector<VkImage> m_swapchainImages;
        std::vector<VkImageView> m_swapchainImageViews;
        // Other Vulkan objects like command buffers, pipelines, etc.
    };
};

#endif // ANTUTU_RHI_VULKAN_RENDER_HPP