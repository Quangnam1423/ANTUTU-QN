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

#include "ATNormalMutex.h"
 
namespace Antutu {
    // ==========================constructor=========================
    ATNormalMutex::ATNormalMutex() 
    {
    }

    // ==========================destructor=========================
    ATNormalMutex::~ATNormalMutex() 
    {
    }

    // =========================public methods==================================
    /**
     * @brief Lock the mutex. Blocks if the mutex is already locked.
     */
    void ATNormalMutex::lock() 
    {
        m_mutex.lock();
    }

    /**
     * @brief Unlock the mutex.
     */
    void ATNormalMutex::unlock() 
    {
        m_mutex.unlock();
    }

    /**
     * @brief Try to lock the mutex without blocking.
     * @return true if the lock was acquired, false otherwise.
     */
    bool ATNormalMutex::tryLock() 
    {
        return m_mutex.try_lock();
    }

    /**
     * @brief Get the native handle of the underlying mutex.
     * @return The native handle of the mutex.
     */
    std::mutex::native_handle_type ATNormalMutex::getNativeHandle() 
    {
        return m_mutex.native_handle();
    }
} // End of Antutu namespace