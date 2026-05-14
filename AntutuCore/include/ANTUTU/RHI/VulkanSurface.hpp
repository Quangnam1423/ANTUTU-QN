#ifndef ANTUTU_RHI_VULKAN_SURFACE_HPP
#define ANTUTU_RHI_VULKAN_SURFACE_HPP

#include <ANTUTU/RHI/IWindow.hpp>
#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <Common/Logger/LogManager.h>

namespace att::RHI
{
	class ANTUTU_API VulkanSurface
	{
	public:
		VulkanSurface() = default;

		~VulkanSurface();

		VulkanSurface(const VulkanSurface&) = delete;

		VulkanSurface& operator=(const VulkanSurface&) = delete;

		bool Initialize(const VulkanInstance&, const ISurfaceProvider&);

		void Destroy();

		VkSurfaceKHR GetHandle() const { return m_surface; }

	// attributes
	private:
		VkInstance m_instance = VK_NULL_HANDLE;
		VkSurfaceKHR m_surface = VK_NULL_HANDLE;
	};
};

#endif // ANTUTU_RHI_VULKAN_SURFACE_HPP