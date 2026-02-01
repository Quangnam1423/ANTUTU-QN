#ifndef ANTUTU_VULKAN_EXTENSION_MANAGER_HPP
#define ANTUTU_VULKAN_EXTENSION_MANAGER_HPP

#include <vector>
#include <string>
#include "VulkanCommon.hpp"

namespace att
{
    class ANTUTU_API VulkanExtensionManager
    {
    public:
        VulkanExtensionManager() = default;
        ~VulkanExtensionManager() = default;

        void AddExtension(const char* extensionName);
        void AddExtension(std::string& ext);
        
        void AddLayer(const char* layer);
        void AddLayer(std::string& layer);

        const std::vector<const char*>& GetExtensions() const { return m_extensions; }
        const std::vector<const char*>& GetLayers() const { return m_layers; }

    private:
        std::vector<const char*> m_extensions;
        std::vector<const char*> m_layers;
    };
}

#endif // ANTUTU_VULKAN_EXTENSION_MANAGER_HPP