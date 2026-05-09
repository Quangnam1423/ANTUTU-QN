#ifndef LOG_MESSAGE_H
#define LOG_MESSAGE_H

#include <Common/Config.h>
#include <string>

namespace Common
{
	enum COMMON_API LogLevel 
	{
		Debug = 0,
		Info,
		Warning,
		Error,
		Critical
	};

	struct COMMON_API LogMessage
	{
		LogLevel level;
		std::string message;
		std::string timestamp;
		LogMessage() = default;
		LogMessage(LogLevel lvl, const std::string& msg, const std::string& time)
			: level(lvl), message(msg), timestamp(time) {}
	};
}

#endif // LOG_MESSAGE_H