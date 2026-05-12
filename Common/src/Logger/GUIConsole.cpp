#include <Common/Logger/GUIConsole.h>
#include <iostream>

namespace Common
{
	void GUIConsole::OnLogReceived(const std::string& msg)
	{
		std::cout << msg << std::endl;
	}
}