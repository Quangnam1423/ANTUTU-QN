#ifndef SANDBOX_WINDOW_HPP
#define SANDBOX_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
// Define macro to glfw expose functions using for Window OS native.
#if defined(_WIN32)
    #define GLFW_EXPOSE_NATIVE_WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <GLFW/glfw3native.h>
// Define macro to glfw expose functions using for Linux OS native.
#elif defined(__linux__)
    #define GLFW_EXPOSE_NATIVE_X11
    #include <GLFW/glfw3native.h>
#endif

#include <string>
#include <memory>

namespace Sandbox
{
    struct WindowPosition {
        int x;
        int y;
    };
    
    struct Vector2f {
        float x;
        float y;
    };

    struct Vector2i {
        int x;
        int y;
    };

    struct WindowConfig {
        int width = 800;
        int height = 600;
        std::string title = "Sandbox Antutu Window";
        Vector2f windowPosition;
        Vector2i windowSize;
    };

    class Window
    {
    public:
        Window(int width = 800, int height = 600, const std::string& title = "Sandbox Antutu Window");
        ~Window();

        Window(const Window&) = delete;                                 // delete copy constructor
        Window& operator=(const Window&) = delete;                      // delete copy assignment
        Window(Window&&) = delete;                                      // delete move constructor
        Window& operator=(Window&&) = delete;                           // delete move assignment

        void Render();
        void PollEvents();
        bool ShouldClose() const;
        GLFWwindow* GetGLFWWindow() const { return m_window; }
    private:
        void InitWindow();
        void Cleanup();
    private:
        WindowConfig m_config;
        GLFWwindow* m_window;
    };
}


#endif // SANDBOX_WINDOW_HPP