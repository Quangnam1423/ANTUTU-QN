#ifndef SHARE_CONTAINER_H
#define SHARE_CONTAINER_H

#include <mutex>
#include <shared_mutex>
#include <Common/Config.h>

namespace Common
{
	template<typename T>
	class COMMON_API ShareContainer
	{
	public:
		using ValueType = typename T::value_type;

		// using for push a value to vector, queue, stack, etc.
		void Push(const ValueType& value)
		{
			std::unique_lock lock(m_mutex);
			if constexpr (requires {m_container.push_back(value);  }) {
				m_container.push_back(value);
			} else {
				m_container.insert(value);
			}
		}

		bool TryPop(ValueType& outValue)
		{
			std::unique_lock lock(m_mutex);
			if (m_container.empty()) return false;

			if constexpr (requires {m_container.front(); })
			{
				outValue = std::move(m_container.front());
				m_container.pop();
			}
			else
			{
				outValue = std::move(m_container.top());
				m_container.pop();
			}
			return true;
		}

	protected:
		T m_container;
		mutable std::shared_mutex m_mutex;
	};
}


#endif	 // SHARE_CONTAINER_H