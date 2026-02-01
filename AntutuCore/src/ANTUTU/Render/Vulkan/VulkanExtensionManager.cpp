#include "ANTUTU/Render/Vulkan/VulkanExtensionManager.hpp"

namespace att
{
    void VulkanExtensionManager::AddExtension(const char* extensionName)
    {
        // validate input
        if (extensionName == nullptr)
        {
            throw std::invalid_argument("Extension name cannot be null");
        }
        size_t len = std::strlen(extensionName);
        // allocate memory for the copy
        char* extCopy = new char[len + 1];
        std::strcpy(extCopy, extensionName);
        // store the copy
        m_extensions.push_back(extCopy);
    }

    void VulkanExtensionManager::AddExtension(std::string& ext)
    {
        // validate input
        if (ext.empty())
        {
            throw std::invalid_argument("Extension name cannot be empty");
        }
        // delegate to the const char* version
        AddExtension(ext.c_str());
        return;
    }

    void VulkanExtensionManager::AddLayer(const char* layer)
    {
        // validate input
        if (layer == nullptr)
        {
            throw std::invalid_argument("Layer name cannot be null");
        }
        size_t len = std::strlen(layer);
        // allocate memory for the copy
        char* layerCopy = new char[len + 1];
        std::strcpy(layerCopy, layer);
        // store the copy
        m_layers.push_back(layerCopy);
        return;
    }

    void VulkanExtensionManager::AddLayer(std::string& layer)
    {
        // validate input
        if (layer.empty())
        {
            throw std::invalid_argument("Layer name cannot be empty");
        }
        // delegate to the const char* version
        AddLayer(layer.c_str());
        return;
    }
}