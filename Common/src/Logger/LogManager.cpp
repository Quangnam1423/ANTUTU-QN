#include <Common/Logger/LogManager.h>

namespace Common
{
	void LogManager::Init()
	{
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		console_sink->set_pattern("%^[%Y-%m-%d %T] %n: %v%$");

        m_observerSink = std::make_shared<Common::ObserverSink_mt>();
		m_observerSink->set_pattern("[%Y-%m-%d %T] [%l] %v");

		std::vector<spdlog::sink_ptr> sinks{ m_observerSink };

		spdlog::init_thread_pool(8192, 1);

        m_coreLogger = std::make_shared<spdlog::async_logger>("Antutu", 
			sinks.begin(), sinks.end(),
			spdlog::thread_pool(),
			spdlog::async_overflow_policy::block
		);
        spdlog::register_logger(m_coreLogger);

        m_coreLogger->set_level(spdlog::level::trace);
        m_coreLogger->flush_on(spdlog::level::err);
	}

	void LogManager::AddObserver(std::shared_ptr<ILogObserver> observer)
	{
		if (m_observerSink)
		{
			m_observerSink->AddObserver(observer);
		}
	}
}