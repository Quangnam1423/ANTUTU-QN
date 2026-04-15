/*
 * InstanceDescriptor.hpp
 *
 *  Created on: 4/16/2026
 *      Author: Quangnam1423
 * 
 *   Description: This file defines the InstanceDescriptor structure, 
 *      which encapsulates the necessary information for creating a Vulkan instance. 
 *  It includes application and engine details, API version, 
 *      required extensions and layers, and flags for enabling validation 
 *      layers and debug messenger.
 */

#ifndef ANTUTU_RHI_INSTANCE_DESCRIPTOR_HPP
#define ANTUTU_RHI_INSTANCE_DESCRIPTOR_HPP

#include <ANTUTU/VulkanCommon.hpp>

#include <vector>
#include <string>
#include <cstring>

namespace att::RHI
{
    ////////////////////////////////////////////////////////////////////////////
    /// Queue Family Indices Structure
    ////////////////////////////////////////////////////////////////////////////
    struct ANTUTU_API InstanceDescriptor
    {
        // Add necessary fields for Vulkan context creation
        const char* applicationName;
        uint32_t applicationVersion;
        const char* engineName;
        uint32_t engineVersion;
        uint32_t apiVersion;
        std::vector<const char*> extensions;
        std::vector<const char*> layers;
        bool isEnableValidationLayers;
        bool isEnableDebugMessenger;
    };
};

#endif // ANTUTU_RHI_INSTANCE_DESCRIPTOR_HPP