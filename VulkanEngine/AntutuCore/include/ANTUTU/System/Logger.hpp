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

namespace att
{
namespace System
{
    /////////////////////////////////////////////////////////////////////////////
    /// Log Level Enumeration
    /////////////////////////////////////////////////////////////////////////////
    enum class ANTUTU_API LogLevel
    {
        INFO,
        WARNING,
        ERROR
    };


    /////////////////////////////////////////////////////////////////////////////
    /// Module Name Enumeration
    /////////////////////////////////////////////////////////////////////////////
    enum class ANTUTU_API ModuleName
    {
        CORE,
        RENDER,
        SYSTEM,
        APPLICATION
    };

    /////////////////////////////////////////////////////////////////////////////
    /// Log Entry Structure & Log declaration 
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Log Callback Function Type
     */
    using LogCallbackFunction = std::function<void(ModuleName, LogLevel, const std::string&)>;

    /////////////////////////////////////////////////////////////////////////////
    /// Logger Class
    /////////////////////////////////////////////////////////////////////////////
    class ANTUTU_API Logger : public NormalMutex
    {
    public:
        /**
         * @brief Log an informational message
         * 
         * @param message The message to log
         */
        static void Info(const std::string& message);

        /**
         * @brief Log a warning message
         * 
         * @param message The message to log
         */
        static void Warning(const std::string& message);

        /**
         * @brief Log an error message
         * 
         * @param message The message to log
         */
        static void Error(const std::string& message);

    private:
        static std::vector<LogCallbackFunction> m_listeners;
    };
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