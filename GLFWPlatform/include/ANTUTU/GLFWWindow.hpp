#ifndef ANTUTU_GLFW_WINDOW_HPP
#define ANTUTU_GLFW_WINDOW_HPP

#include <ANTUTU/Config.hpp>

namespace att::GLFW
{
	class GLFW_PLATFORM_API GLFWWindow
	{
	public:
		GLFWWindow(int width, int height, const std::string& title);
		~GLFWWindow();
		void Render();
		std::vector<const char*> GetRequiredExtensions() const;
		void* GetNativeWindow() const { return m_window; }
	private:
		void InitWindow();
		void Cleanup();
		struct WindowConfig
		{
			int width;
			int height;
			std::string title;
			glm::vec2 windowSize;
			glm::vec2 windowPosition;
		};
		WindowConfig m_config;
		GLFWwindow* m_window;
	};
};

#endif // ANTUTU_GLFW_WINDOW_HPP