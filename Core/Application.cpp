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

#include "Core/Application.hpp"




// //#include "Core/Logger.hpp"

// #include <GLFW/glfw3.h>
// #include <iostream>

// namespace Antutu {

//     Application::Application(const AppConfig& config)
//         : m_config(config)
//     {
//         Logger::init(); // initialize logging system
//         AN_LOG_INFO("Application initializing: {}", config.title);

//         initWindow();
//         initSubsystems();
//     }

//     Application::~Application() {
//         AN_LOG_INFO("Shutting down Application...");
//         onShutdown();
//         glfwTerminate();
//     }

//     void Application::initWindow() {
//         m_mainWindow = std::make_unique<GLFWWindow>(
//             m_config.width,
//             m_config.height,
//             m_config.title.c_str()
//         );

//         m_mainWindow->setCloseCallback([this]() {
//             this->close();
//         });

//         m_mainWindow->setResizeCallback([this](int w, int h) {
//             if (w == 0 || h == 0)
//                 m_minimized = true;
//             else
//                 m_minimized = false;
//         });

//         AN_LOG_INFO("Window initialized successfully.");
//     }

//     void Application::initSubsystems() {
//         Input::initialize();
//         // Time::initialize();
//         // Renderer::initialize();
//         // IPCManager::initialize();
//     }

//     void Application::run() {
//         onInit();
//         m_running = true;
//         m_lastFrameTime = std::chrono::steady_clock::now();

//         AN_LOG_INFO("Application started.");

//         while (m_running && !m_mainWindow->shouldClose()) {
//             pollEvents();

//             auto now = std::chrono::steady_clock::now();
//             float deltaTime = std::chrono::duration<float>(now - m_lastFrameTime).count();
//             m_lastFrameTime = now;

//             if (!m_minimized) {
//                 onUpdate(deltaTime);
//                 m_mainWindow->swapBuffers();
//             }
//         }

//         onShutdown();
//         AN_LOG_INFO("Application stopped.");
//     }

//     void Application::pollEvents() {
//         glfwPollEvents();
//         // handle queued events if needed
//     }

//     void Application::close() {
//         m_running = false;
//     }

// } // namespace Antutu