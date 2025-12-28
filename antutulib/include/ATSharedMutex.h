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
#ifndef ANTUTU_ATSHAREDMUTEX_HPP
#define ANTUTU_ATSHAREDMUTEX_HPP

#include <shared_mutex>

namespace Antutu {

    /**
     * @class ATSharedMutex
     * @brief A shared mutex implementation using std::shared_mutex.
     * This class provides functionalities for exclusive and shared locking,
     * unlocking, and try-locking.
     * @author Quangnam1423
     */
    class ATSharedMutex {
    protected:
        // ==========================constructor=========================
        ATSharedMutex();   
        ~ATSharedMutex();
        // =========================methods==================================
        void lock();
        void unlock();
        bool tryLock();
        void lockShared();
        void unlockShared();
        bool tryLockShared();
    private:
        std::shared_mutex m_mutex;
    }; // End of ATSharedMutex class    
} // End of Antutu namespace

#endif // ANTUTU_ATSHAREDMUTEX_HPP