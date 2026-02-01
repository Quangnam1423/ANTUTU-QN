#include "ANTUTU/Render/Vulkan/GLFWVulkanPlatform.hpp"

namespace att
{
    std::vector<const char*> GLFWVulkanPlatform::GetRequiredInstanceExtensions() const
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions;
        for (uint32_t i = 0; i < glfwExtensionCount; i++)
        {
            extensions.push_back(glfwExtensions[i]);
        }
        return extensions;
    }

    void GLFWVulkanPlatform::createSurface(vk::Instance instance, VkSurfaceKHR* outSurface) const
    {
        if (glfwCreateWindowSurface(static_cast<VkInstance>(instance), 
                                    glfwGetCurrentContext(), 
                                    nullptr, 
                                    outSurface) != VK_SUCCESS) 
        {
            throw std::runtime_error("Failed to create GLFW window surface!");
        }
    }
}