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

#ifndef ANTUTU_COMMON_NORMALMUTEX_HPP
#define ANTUTU_COMMON_NORMALMUTEX_HPP

#include "ANTUTU/Config.hpp"
#include <mutex>

namespace att
{
    /////////////////////////////////////////////////////////////////////////////
    /// Normal Mutex Class
    /////////////////////////////////////////////////////////////////////////////
    class NormalMutex
    {
    protected:
        /**
         * @brief Constructor
         * 
         */
        NormalMutex() = default;

        /**
         * @brief Destructor
         * 
         */
        virtual ~NormalMutex();

        /**
         * @brief Lock the mutex
         * 
         */
        void lock();

        /**
         * @brief Unlock the mutex
         * 
         */
        void unlock();
    private:
        // Platform-specific mutex implementation can be added here.
        std::mutex m_mutex;
    };
}

#endif // ANTUTU_COMMON_NORMALMUTEX_HPP