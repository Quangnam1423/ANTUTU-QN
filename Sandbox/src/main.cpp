#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <Object/Window.hpp>
#include <Common/Logger/LogManager.h>
#include <Common/Logger/GUIConsole.h>
#include <Sandbox.hpp>

#if defined(_WIN32) && defined(_MSC_VER)
    #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
    SB::Sandbox* app = new SB::Sandbox();

	app->Initialize();

	app->Run();

    if (1)
    {
        app->Shutdown();
    }

    delete app;

    return EXIT_SUCCESS;
}