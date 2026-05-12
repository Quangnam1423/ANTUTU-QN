#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <Common/Config.h>
#include <Common/Logger/ObserverSink.h>
#include <shared_mutex>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>	

namespace Common
{
	class COMMON_API LogManager
	{
	public:
		static LogManager& Get()
		{
			static LogManager instance;
			return instance;
		}

		void Init();
		void AddObserver(std::shared_ptr<ILogObserver> observer);
		inline std::shared_ptr<spdlog::async_logger>& GetLogger() { return m_coreLogger; }
	private: 
		LogManager() = default;
		std::shared_ptr<spdlog::async_logger> m_coreLogger;
		std::shared_ptr<Common::ObserverSink_mt> m_observerSink;
	};


	#define LOG_TRACE(...)    LogManager::Get().GetLogger()->trace(__VA_ARGS__)
	#define LOG_INFO(...)     LogManager::Get().GetLogger()->info(__VA_ARGS__)
	#define LOG_WARN(...)     LogManager::Get().GetLogger()->warn(__VA_ARGS__)
	#define LOG_ERROR(...)    LogManager::Get().GetLogger()->error(__VA_ARGS__)
	#define LOG_CRITICAL(...) LogManager::Get().GetLogger()->critical(__VA_ARGS__)
}


#endif