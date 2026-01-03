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

// =========================GLFWWindow.cpp=========================
#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <unordered_map>
#include <cstdint>

namespace Antutu {
    template<typename... Args>
    class Signal {
    public:
        using CallbackType = std::function<void(Args...)>;                  // Define the callback type

        Signal() = default;                                                  // default constructor
        ~Signal() = default;                                                 // default destructor

        Signal(const Signal&) = delete;                                     // delete copy constructor
        Signal& operator=(const Signal&) = delete;                          // delete copy assignment
        Signal(Signal&&) = delete;                                          // delete move constructor
        Signal& operator=(Signal&&) = delete;                               // delete move assignment

        /**
         * @brief Subscribe to the event with a callback function.
         * @param callback The callback function to be invoked when the event is triggered.(normal function, lambda, functor  etc.)
         * @return A unique ID for the subscription, used for unsubscription.
         */
        uint64_t subscribe(const CallbackType& callback) {
            uint64_t id = m_nextID++;
            m_listeners[id] = callback;
            return id;
        }

        /**
         * @brief Unsubscribe from the event using the unique ID.
         * @param id The unique ID of the subscription to be removed.
         * @return True if the subscription was successfully removed, false otherwise.
         */
        bool unsubscribe(uint64_t id) {
            return m_listeners.erase(id) > 0;
        }

        /**
         * @brief Clear all subscriptions from the event.
         */
        void clear() {
            m_listeners.clear();
        }



        /**
         * @brief Functor operator to invoke the event.
         * @param args The arguments to be passed to the callbacks.
         */
        void operator()(Args... args) {
            invoke(args...);
        }

    private:

        /**
         * @brief Invoke all subscribed callbacks with the provided arguments.
         * @param args The arguments to be passed to the callbacks.
         */
        void invoke(Args... args) {
            for (const auto& [id, callback] : m_listeners) {
                if (callback) {
                    callback(args...);
                }
            }
        }

    private:
        std::unordered_map<uint64_t, CallbackType> m_listeners;
        uint64_t m_nextID = 0;
    };
} // namespace Antutu

#endif // SIGNAL_HPP