#ifndef I_LOG_OBSERVER_H
#define I_LOG_OBSERVER_H

#include <Common/Config.h>
#include <string>

namespace Common
{
	class COMMON_API ILogObserver
	{
	public:
		virtual ~ILogObserver() = default;
		virtual void OnLogReceived(const std::string& msg) = 0;
	};
}

#endif // I_LOG_OBSERVER_H