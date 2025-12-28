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
#ifndef ANTUTU_ATNORMALMUTEX_HPP
#define ANTUTU_ATNORMALMUTEX_HPP

#include <mutex>

namespace Antutu {  
    /**
     * @class ATNormalMutex
     * @brief A normal mutex implementation using std::mutex.
     * This class provides basic mutex functionalities such as locking,
     * unlocking, and try-locking.
     * @author Quangnam1423
     */
    class ATNormalMutex {
    protected:
        // ==========================constructor=========================
        ATNormalMutex();   
        ~ATNormalMutex();
        // =========================methods==================================
        void lock();
        void unlock();
        bool tryLock();
        std::mutex::native_handle_type getNativeHandle();
    private:
        std::mutex m_mutex;
}; // End of ATNormalMutex class

} // End of Antutu namespace

#endif // ANTUTU_ATNORMALMUTEX_HPP
