/*
Antutu Vulkan Engine
Copyright (C) 2025 Quangnam1423

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
// =========================GLFWWindow.hpp=========================

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>
#include <string>
#include <vector>
#include <chrono>

// namespace Antutu {
//     class GLFWWindow;  // Window Object
//     class Event;      // Event Object
//     class VulkanContext;    // Vulkan Context Object
//     class VulkanSwapchain;
//     class VulkanRenderer;
//     class VulkanInstance;
//     class ImGuiLayer;
// }
// =========================Forward declarations=========================

namespace Antutu {
    class Window;  // Window Object
    class Event;
    class LayerStack;
    class ImGuiLayer;
    class Renderer;
    class VulKanContext;
    class VulkanSwapchain;

    class WindowCloseEvent;
    class WindowResizeEvent;
}

namespace Antutu {

// ===========Configuration structure for the application==================
struct AppConfig {
    std::string title;
    uint32_t width;
    uint32_t height;
    bool enableVSync;
    bool enableValidation;
    bool enableImGui;
};

// =========================Application Class=========================
class Application {
public:
    Application(const AppConfig& config);
    virtual ~Application();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    void Run();
    void PushLayer(class Layer* layer);
    void PushOverlay(class Layer* layer);
    void PostEvent(Event& e);
    void Close();


    Window& GetWindow() const { return *m_window; }
    Renderer& GetRenderer() const { return *m_renderer; }
    VulkanSwapchain& GetSwapchain() const { return *m_swapchain; }
    ImGuiLayer& GetImGuiLayer() const { return *m_imGuiLayer; }
    const AppConfig& GetConfig() const { return m_config; }

    static Application& Get() { return *s_instance; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);
private:
    static Application* s_instance;

    AppConfig m_config;
    bool m_isRunning = true;
    bool m_minimized = false;
    float m_lastFrameTime = 0.0f;

    Window* m_window;
    VulKanContext* m_vulkanContext;
    VulkanSwapchain* m_swapchain;
    Renderer* m_renderer;
    LayerStack* m_layerStack;

    ImGuiLayer* m_imGuiLayer;
};

extern Application* CreateApplication();

}

#endif // APPLICATION_HPP namespace Antutu