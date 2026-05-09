/**
* ShareContextBase
* Using this class to heritage and create a share context class.
* But just for string of simple data that has a determined size,
* not for complex data like vector, map, etc.
* Recommend to use this class for share context that read more than write,
* because of the lock mechanism.
*/


#ifndef SHARE_CONTEXT_BASE_H
#define SHARE_CONTEXT_BASE_H

#include <mutex>
#include <shared_mutex>
#include <Common/Config.h>

namespace Common
{
	template<typename T>
	class COMMON_API ShareContextBase
	{
	public:
		ShareContextBase() = default;
		explicit ShareContextBase(const T& contextValue) : m_context(contextValue) {}
		explicit ShareContextBase(T&& contextValue) : m_context(std::move(contextValue)) {}
		virtual ~ShareContextBase() = default;

	public:
		void SetValue(const T& value)
		{
			std::unique_lock<std::shared_mutex> lock(m_mutex);
			m_context = value;
		}

		T GetValue() const
		{
			std::shared_lock<std::shared_mutex> lock(m_mutex);
			return m_context;
		}
	protected:
		std::shared_mutex m_mutex;
		T m_context;
	};
}


#endif	// SHARE_CONTEXT_BASE_H