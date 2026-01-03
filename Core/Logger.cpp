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

#include "Core/Logger.hpp"

namespace Antutu {

    std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
    std::shared_ptr<UISink> Logger::s_UISink;

    void Logger::Init() {
        s_UISink = std::make_shared<UISink>();

        // Console sink (màu)
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%T] %n: %v%$");

        // File sink
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Antutu.log", true);

        // Gom sinks lại
        std::vector<spdlog::sink_ptr> coreSinks = { consoleSink, fileSink, s_UISink };
        std::vector<spdlog::sink_ptr> clientSinks = { consoleSink, fileSink, s_UISink };

        s_CoreLogger = std::make_shared<spdlog::logger>("ANTUTU", coreSinks.begin(), coreSinks.end());
        s_ClientLogger = std::make_shared<spdlog::logger>("APP", clientSinks.begin(), clientSinks.end());

        spdlog::register_logger(s_CoreLogger);
        spdlog::register_logger(s_ClientLogger);

        s_CoreLogger->set_level(spdlog::level::trace);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
    }

} // namespace Antutu