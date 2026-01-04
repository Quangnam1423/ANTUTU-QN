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

#include "ANTUTU/System/Logger.hpp"

namespace att
{
namespace System
{
    Logger::Logger() : m_isRunning(true)
    {
    }

    /// @brief destructor
    Logger::~Logger()
    {
        lock();
        m_listeners.clear();
        unlock();
    }

    /// @brief      
    /// @param module 
    /// @param level 
    /// @param message 
    void Logger::WriteLog(ModuleName module, LogLevel level, const std::string& message)
    {
        // for now, we have no validation path.
        LogMessage msg;
        msg.message         = message;
        msg.module          = module;
        msg.level           = level;
        // push message to queue.
        lock();
        m_messageQueue.push(msg);
        unlock();

        return;
    }

    /// @brief  
    /// @param msg 
    void Logger::WriteLog(LogMessage msg)
    {
        lock();
        m_messageQueue.push(msg);
        unlock();

        return;
    }

    /// @brief  
    /// @param callback 
    void Logger::AddListener(LogCallbackFunction callback)
    {
        m_listeners.push_back(callback);
    }

    /// @brief  
    /// @param log 
    /// @param msg 
    void Logger::WriteLog(void* log, LogMessage msg)
    {
        Logger* logger = static_cast<Logger*>(log);
        logger->WriteLog(msg);
    }

    /// @brief 
    /// @param log 
    /// @param module 
    /// @param level 
    /// @param message 
    void Logger::WriteLog(void* log, ModuleName module, LogLevel level, const std::string& message)
    {
        Logger* logger = static_cast<Logger*>(log);
        logger->WriteLog(module, level, message);
    }

    /// @brief 
    /// @param logger 
    void Logger::StartFunction(void* logger)
    {

    }


    /// @brief 
    void Logger::StartFunction()
    {
        LogMessage msg;
        while(true)
        {
            {
                std::unique_lock<std::mutex> lock(m_workerMutex);
                m_cv.wait(lock, [this]{return !m_messageQueue.empty() || !m_isRunning;} );

                if (!m_isRunning && m_messageQueue.empty())
                {
                    break;
                }
                msg = std::move(m_messageQueue.front());
                m_messageQueue.pop();
            }

            // handle message.
            {
                lock();
                for (const auto& callback : m_listeners)
                {
                    if (callback)
                    {
                        callback(msg.module, msg.level, msg.message);
                    }
                }
                unlock();
            }
        }
    }

} // namespace System
} // namespace att