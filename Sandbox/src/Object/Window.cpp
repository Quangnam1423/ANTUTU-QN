#include <Object/Window.hpp>
#include <stdexcept>

namespace Sandbox
{
    Window::Window(int width, int height, const std::string& title)
        : m_config{width, height, title}, m_window(nullptr)
    {
        InitWindow();
    }

    Window::~Window()
    {
        Cleanup();
    }

    void Window::Render()
    {
        while (!ShouldClose()) {
            PollEvents();
            // Rendering code will go here in the future
        }
    }

    std::vector<const char*> Window::GetRequiredExtensions() const
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
    }

    void Window::InitWindow()
    {
        m_config.windowSize = { m_config.width, m_config.height };
        m_config.windowPosition = { 700.0f, 500.0f };
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW!");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        m_window = glfwCreateWindow(m_config.width, m_config.height, m_config.title.c_str(), nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window!");
        }
        glfwMakeContextCurrent(m_window);
        glfwGetWindowSize(m_window, &m_config.windowSize.x, &m_config.windowSize.y);
        glfwGetWindowPos(m_window, (int*)&m_config.windowPosition.x, (int*)&m_config.windowPosition.y);

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        int windowPosX = (mode->width - m_config.windowSize.x) / 2;
        int windowPosY = (mode->height - m_config.windowSize.y) / 2;
        glfwSetWindowPos(m_window, windowPosX, windowPosY);
    }

    void Window::Cleanup()
    {
        if (m_window) {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
        glfwTerminate();
    }

    void Window::PollEvents() 
    {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }
}