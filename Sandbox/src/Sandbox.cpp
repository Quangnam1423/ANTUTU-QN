#include <Sandbox.hpp>
#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <Object/Window.hpp>
#include <Common/Logger/FileLogObserver.h>
#include <Common/Logger/LogManager.h>
#include <Common/Logger/GUIConsole.h>

namespace SB
{
	Sandbox::Sandbox()
	{

	}

	Sandbox::~Sandbox()
	{

	}

	void Sandbox::Initialize()
	{
		// init log manager and add file log observer
		Common::LogManager::Get().Init();
		std::filesystem::path p = "logs";
		p /= "sandbox_log.txt";
		m_fileLogObserver= std::make_shared<Common::FileLogObserver>(p);
		Common::LogManager::Get().AddObserver(m_fileLogObserver);

		// Initialize the window, Vulkan instance, and logging system here
		m_window = new SB::Window(800, 600, "Sandbox Antutu Window");
		LOG_INFO("init window sucessfully.");

		// init vulkan instance with config
		{
			att::PlatformInfo::VulkanInstanceConfig config{
				.appName = "Antutu Vulkan Engine",
				.appVer = VK_MAKE_VERSION(1, 0, 0),
				.engineName = "Antutu Engine",
				.engineVer = VK_MAKE_VERSION(1, 0, 0),
				.apiVer = VK_API_VERSION_1_3,
				.exts = {m_window->GetRequiredExtensions()}
			};

			m_vulkanInstance = new att::RHI::VulkanInstance();

			if (!m_vulkanInstance->Initialize(config)) {
				std::cerr << "Failed to initialize Vulkan instance!" << std::endl;
				LOG_ERROR("Failed to initialize Vulkan instance!");
			}
			else
			{
				LOG_INFO("Vulkan instance initialized successfully!");
			}
		}
		


	}

	void Sandbox::Run()
	{
		LOG_INFO("Sandbox running...");
		m_window->Render();
	}

	void Sandbox::Shutdown()
	{
		Cleanup();
	}

	void Sandbox::Render()
	{

	}

	void Sandbox::Update()
	{

	}

	void Sandbox::HandleEvents()
	{

	}

	void Sandbox::Cleanup()
	{
		delete m_vulkanInstance;
		m_vulkanInstance = nullptr;
	}
}