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

// =========================Antutu::Window.hpp=========================


#ifndef ANTUTU_WINDOW_HPP
#define ANTUTU_WINDOW_HPP

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <string>
namespace Antutu {
    // ======================Window Class Declaration==================

    /**
     * @class Window
     * @brief A class that encapsulates a GLFW window for Vulkan applications.
     * This class handles window creation, event polling, and provides access to the native GLFW window.
     * It initializes GLFW and creates a window with specified dimensions and title.
     * It also ensures proper cleanup of resources upon destruction.
     * @note This class does not create an OpenGL context, as it is intended for Vulkan use.
     * @author Quangnam1423
     */
    class Window {
    public:
        Window();                                                       // constructor
        Window(int width, int height, const std::string& title);        // parameterized constructor
        ~Window();                                                      // destructor 

        Window(const Window&) = delete;                                 // delete copy constructor
        Window& operator=(const Window&) = delete;                      // delete copy assignment
        Window(Window&&) = delete;                                      // delete move constructor
        Window& operator=(Window&&) = delete;                           // delete move assignment

        bool ShouldClose() const;                                       // check if window should close
        void PollEvents() const;                                        // poll window events
        GLFWwindow* GetNativeWindow() const;                            // get the GLFW window pointer

        // ======getter and setter for width and height=================
        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }
        inline void SetWidth(int width) { m_width = width; }
        inline void SetHeight(int height) { m_height = height; }

    private:  // private members
        GLFWwindow* m_window;                                           // GLFW window pointer
        int m_width;                                                    // window width
        int m_height;                                                   // window height
        std::string m_title;                                            // window title
    }; // End of Window class
}

#endif // ANTUTU_WINDOW_HPP