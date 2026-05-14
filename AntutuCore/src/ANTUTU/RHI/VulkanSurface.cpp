#include <ANTUTU/RHI/VulkanSurface.hpp>


namespace att::RHI
{
	VulkanSurface::~VulkanSurface()
	{
		Destroy();
		LOG_INFO("Vulkan surface destroyed.");
	}


	bool VulkanSurface::Initialize(const VulkanInstance& instance, const ISurfaceProvider& surfaceProvider)
	{
		m_instance = instance.GetHandle();

		if (m_instance == VK_NULL_HANDLE) 
		{
			LOG_ERROR("Invalid Vulkan instance provided for surface creation.");
			return false;
		}

		m_surface = surfaceProvider.CreateSurface(m_instance);

		if (m_surface == VK_NULL_HANDLE) 
		{
			LOG_ERROR("Failed to create Vulkan surface.");
			return false;
		}

		LOG_INFO("Vulkan surface created successfully.");
		return true;
	}


	void VulkanSurface::Destroy()
	{
		if (m_surface != VK_NULL_HANDLE) 
		{
			vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
			m_surface = VK_NULL_HANDLE;
		}
	}
}