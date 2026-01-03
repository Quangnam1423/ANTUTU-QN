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

// =========================Antutu::Window.cpp===========================
#include "Window.hpp"
#include <stdexcept>

namespace Antutu 
{
// ==========================default constructor=========================
    Window::Window() 
        : Window(800, 600, "Antutu Window")
    {

    }

// ==========================parameter constructor=========================
    Window::Window(int width, int height, const std::string& title)
        : m_width(width), m_height(height), m_title(title)
    {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // No OpenGL context
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE); // Make window resizable

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
        if (!m_window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
    }

// ================================destructor==============================
    Window::~Window()
    {
        if (m_window) {
            glfwDestroyWindow(m_window);
            m_window = nullptr;
        }
        glfwTerminate();
    }

// =========================public methods==================================
    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::PollEvents() const
    {
        glfwPollEvents();
    }

    GLFWwindow* Window::GetNativeWindow() const
    {
        return m_window;
    }
}