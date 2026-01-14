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

#ifndef ANTUTU_SYSTEM_LOGGER_HPP
#define ANTUTU_SYSTEM_LOGGER_HPP

#include "ANTUTU/Config.hpp"
#include "ANTUTU/Common/NormalMutex.hpp"

// Standard Library Includes
#include <string>
#include <optional>
#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>
#include <functional>
#include <atomic>
#include <unordered_map>
#include <condition_variable>
#include <thread>
#include <queue>

namespace att
{
namespace System
{
    /////////////////////////////////////////////////////////////////////////////
    /// Log Level Enumeration
    /////////////////////////////////////////////////////////////////////////////
    enum class ANTUTU_API LogLevel
    {
        LOG_INFO = 0,
        LOG_WARNING,
        LOG_ERROR,
        LOG_DEBUG
    };


    /////////////////////////////////////////////////////////////////////////////
    /// Module Name Enumeration
    /////////////////////////////////////////////////////////////////////////////
    enum class ANTUTU_API ModuleName
    {
        MODULE_CORE = 0,
        MODULE_RENDER,
        MODULE_SYSTEM,
        MODULE_APPLICATION
    };

    /////////////////////////////////////////////////////////////////////////////
    /// Log Entry Structure & Log declaration 
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Log Callback Function Type.
     */
    typedef std::function<void(System::ModuleName, LogLevel, const std::string&)> LogCallbackFunction;

    /**
     * @brief use for ListenerID stand for a callback function - listener.
     */
    typedef uint32_t ListenerID;

    /**
     * @brief define a message log packet.
     */
    typedef struct DefineLOGMESSAGE
    {
        std::string message;
        ModuleName module;
        LogLevel level;
    } LogMessage;


    /////////////////////////////////////////////////////////////////////////////
    /// CallbackManager class
    /////////////////////////////////////////////////////////////////////////////
    // class ANTUTU_API CallbackManager : public NormalMutex
    // {
    // public:
    //     CallbackManager() = default;
    //     virtual ~CallbackManager();
    //     ListenerID AddListener(LogCallbackFunction callback);
    //     bool RemoveListener(ListenerID);
    //     void SendLog()
    // private:
    //     std::unordered_map<ListenerID, LogCallbackFunction> m_listeners;
    //     std::atomic<ListenerID> m_nextID;
    
    // }; // end CallbackManager declaration.



    /////////////////////////////////////////////////////////////////////////////
    /// Logger Class
    /////////////////////////////////////////////////////////////////////////////
    class ANTUTU_API Logger : public NormalMutex
    {
    public:
        /**
         * default constructor
         */
        Logger();

        /**
         * default destructor
         */
        virtual ~Logger();

        void WriteLog(ModuleName module, LogLevel level, const std::string& message);
        void WriteLog(LogMessage msg);

        void AddListener(LogCallbackFunction callback);

        //void SendMessage()
    public:
        static void WriteLog(void* log, LogMessage msg);
        static void WriteLog(void* log, ModuleName module, LogLevel level, const std::string& message);
        static void StartFunction(void* logger);

    private: 
        void StartFunction();

    private:
        std::string                             m_name;
        std::vector<LogCallbackFunction>        m_listeners;
        std::queue<LogMessage>                  m_messageQueue;
        std::condition_variable                 m_cv;
        std::atomic<bool>                       m_isRunning;
        std::thread                             m_workerThread; 
        std::mutex                              m_workerMutex; 
    }; // end Logger declaration.


} // namespace System
} // namespace att

#endif // ANTUTU_SYSTEM_LOGGER_HPP


/**
 * @file Logger.hpp
 * @brief Declaration of the Logger class for logging messages.
 * @author Quangnam1423
 * @date 2025
 * Copyright (C) 2025 Quangnam1423
 * 
 * This file declares the Logger class which provides static methods
 * for logging informational, warning, and error messages.
 * The Logger class can be extended to include more features such as
 * logging to files, different log levels, and module-specific logging.
 * Example:
 * Logger::Info("This is an informational message.");
 * Logger::Warning("This is a warning message.");
 * Logger::Error("This is an error message.");
 * Logger::WriteLog(ModuleName::CORE, LogLevel::ERROR, "Core module error occurred.");
 * Logger::ReadLog();
 * Logger::SetLogFile("application.log");
 */