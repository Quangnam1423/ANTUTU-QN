#ifndef OBSERVER_SINK_H
#define OBSERVER_SINK_H

#include <Common/Config.h>
#include <Common/DTO/LogMessage.h>
#include <Common/Logger/ILogObserver.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/null_mutex.h>
#include <vector>
#include <mutex>
#include <algorithm>
#include <iostream>

namespace Common
{
	template<typename Mutex>
	class ObserverSink : public spdlog::sinks::base_sink<Mutex>
	{
	public: 
		void AddObserver(std::shared_ptr<ILogObserver> observer)
		{
			std::lock_guard<std::mutex> lock(m_obsMutex);
			m_observers.push_back(observer);
		}

		void RemoveObserver(std::shared_ptr<ILogObserver> observer)
		{
			std::lock_guard<std::mutex> lock(m_obsMutex);
			m_observers.erase(
				std::remove_if(m_observers.begin(), m_observers.end(),
					[&observer](const std::weak_ptr<ILogObserver>& wp) {
						return wp.expired() || wp.lock() == observer;
					}),
				m_observers.end()
			);
		}
	protected:
		void sink_it_(const spdlog::details::log_msg& msg) override
		{
			spdlog::memory_buf_t formatted;
			spdlog::sinks::base_sink<Mutex>::formatter_->format(msg, formatted);

			std::string detailMsg = fmt::to_string(formatted);
			std::lock_guard<std::mutex> lock(m_obsMutex);
			for (auto& weak_obs : m_observers)
			{
				if (auto obs = weak_obs.lock())
				{
					obs->OnLogReceived(detailMsg);
				}
			}
		}

		void flush_() override {}
	private:
		std::vector<std::weak_ptr<ILogObserver>> m_observers;
		std::mutex m_obsMutex;
	};

	using ObserverSink_mt = ObserverSink<std::mutex>;
	using ObserverSink_st = ObserverSink<spdlog::details::null_mutex>;
}

#endif // OBSERVER_SINK_H