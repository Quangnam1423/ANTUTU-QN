#ifndef SANDBOX_H
#define SANDBOX_H

#include <State/SandBoxState.hpp>

namespace att
{
	namespace RHI
	{
		class VulkanInstance;
	}
}

namespace Common
{
	class FileLogObserver;
}

namespace SB
{
	// Forward declaration of Window class to avoid circular dependency
	class Window;

	// The Sandbox class serves as the main application class that manages the application lifecycle,
	// including initialization, main loop, and shutdown. 
	// It interacts with the Window class to create a window and handle rendering and events.
	class Sandbox
	{
	public:
		Sandbox();
		~Sandbox();
		void Initialize();
		void Run();
		void Shutdown();
	private:
		void Render();
		void Update();
		void HandleEvents();
		void Cleanup();
	private:
		SB::Window* m_window;
		att::RHI::VulkanInstance* m_vulkanInstance;
		std::shared_ptr<Common::FileLogObserver> m_fileLogObserver;

		bool m_isRunning;
	};
}

#endif	// SANDBOX_H