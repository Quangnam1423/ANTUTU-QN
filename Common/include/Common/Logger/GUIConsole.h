#ifndef CONSOLE_SINK_H
#define CONSOLE_SINK_H

#include <Common/Logger/ILogObserver.h>

namespace Common
{
	class COMMON_API GUIConsole : public ILogObserver
	{
	public:
		void OnLogReceived(const std::string& msg) override;
	};
}

#endif // CONSOLE_SINK_H