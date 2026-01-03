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

#ifndef ANTUTU_CORE_LOGGER_HPP
#define ANTUTU_CORE_LOGGER_HPP
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/syslog_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/ringbuffer_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Antutu {

    class UISink : public spdlog::sinks::base_sink<std::mutex> 
    {

    public:
        struct LogEntry {
            spdlog::level::level_enum level;
            std::string message;
        };

        const std::vector<LogEntry>& getLogEntries() const {
            return m_logEntries;
        }

    private:
        void sink_it_(const spdlog::details::log_msg& msg) override {
            spdlog::memory_buf_t formatted;
            base_sink<std::mutex>::formatter_->format(msg, formatted);

            LogEntry entry;
            entry.message = fmt::to_string(formatted);
            entry.level = msg.level;
            m_logEntries.push_back(entry);
        }

        void flush_() override {}

    private:
        std::vector<LogEntry> m_logEntries;

    };

    class Logger {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

        static std::shared_ptr<UISink> GetUISink() { return s_UISink; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
        static std::shared_ptr<UISink> s_UISink;
    };

} // namespace Antutu



// ======== Macros ========
#define AN_CORE_TRACE(...)     ::Antutu::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define AN_CORE_INFO(...)      ::Antutu::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define AN_CORE_WARN(...)      ::Antutu::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define AN_CORE_ERROR(...)     ::Antutu::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define AN_CORE_CRITICAL(...)  ::Antutu::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define AN_TRACE(...)          ::Antutu::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define AN_INFO(...)           ::Antutu::Logger::GetClientLogger()->info(__VA_ARGS__)
#define AN_WARN(...)           ::Antutu::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define AN_ERROR(...)          ::Antutu::Logger::GetClientLogger()->error(__VA_ARGS__)
#define AN_CRITICAL(...)       ::Antutu::Logger::GetClientLogger()->critical(__VA_ARGS__)


#endif // ANTUTU_CORE_LOGGER_HPP