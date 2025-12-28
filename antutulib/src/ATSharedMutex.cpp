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

#include "ATSharedMutex.h"

namespace Antutu {
    // ==========================constructor=========================
    ATSharedMutex::ATSharedMutex() 
    {
    }

    // ==========================destructor=========================
    ATSharedMutex::~ATSharedMutex() 
    {
    }

    // =========================public methods==================================
    /**
     * @brief Lock the mutex for exclusive access. Blocks if the mutex is already locked.
     */
    void ATSharedMutex::lock() 
    {
        m_mutex.lock();
    }

    /**
     * @brief Unlock the mutex from exclusive access.
     */
    void ATSharedMutex::unlock() 
    {
        m_mutex.unlock();
    }

    /**
     * @brief Try to lock the mutex for exclusive access without blocking.
     * @return true if the lock was acquired, false otherwise.
     */
    bool ATSharedMutex::tryLock() 
    {
        return m_mutex.try_lock();
    }

    /**
     * @brief Lock the mutex for shared access. Blocks if the mutex is already exclusively locked.
     */
    void ATSharedMutex::lockShared() 
    {
        m_mutex.lock_shared();
    }

    /**
     * @brief Unlock the mutex from shared access.
     */
    void ATSharedMutex::unlockShared() 
    {
        m_mutex.unlock_shared();
    }

    /**
     * @brief Try to lock the mutex for shared access without blocking.
     * @return true if the shared lock was acquired, false otherwise.
     */
    bool ATSharedMutex::tryLockShared() 
    {
        return m_mutex.try_lock_shared();
    }
} // End of Antutu namespace