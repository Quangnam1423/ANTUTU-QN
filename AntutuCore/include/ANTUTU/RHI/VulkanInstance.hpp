#ifndef ANTUTU_RHI_VULKAN_CONTEXT_HPP
#define ANTUTU_RHI_VULKAN_CONTEXT_HPP

#include <ANTUTU/VulkanCommon.hpp>
#include <ANTUTU/RHI/VulkanContext.hpp>
#include <ANTUTU/RHI/InstanceDescriptor.hpp>
#include <ANTUTU/RHI/ISurfaceProvider.hpp>

#include <vector>
#include <string>
#include <optional>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <functional>


namespace att::RHI
{
    using SurfaceCreateProc = std::function<VkSurfaceKHR(VkInstance)>;
    class ANTUTU_API VulkanInstance {
        public:
            VulkanInstance() = default;
            ~VulkanInstance() = default;    

            VulkanInstance(const VulkanInstance&) = delete;
            VulkanInstance& operator=(const VulkanInstance&) = delete;

            void Initialize(const InstanceDescriptor& descriptor, SurfaceCreateProc surfaceCreateProc);

        private:
            void createInstance(const InstanceDescriptor& descriptor);
            void setupDebugMessenger();

        private:
            VkInstance m_instance;
            VkSurfaceKHR m_surface;


    };
};

#endif // ANTUTU_RHI_VULKAN_CONTEXT_HPP