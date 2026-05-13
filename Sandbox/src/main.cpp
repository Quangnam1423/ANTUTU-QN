#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <Object/Window.hpp>
#include <Common/Logger/LogManager.h>
#include <Common/Logger/GUIConsole.h>
#include <Sandbox.hpp>


int main()
{
    //SB::Window window(800, 600, "Sandbox Antutu Window");

    //// init vulkan instance with config


    //Common::LogManager::Get().Init();
    //auto editorUILog = std::make_shared<Common::GUIConsole>();
    //Common::LogManager::Get().AddObserver(editorUILog);



    //window.Render();

    // close app

    SB::Sandbox app;
	app.Initialize();
	app.Run();
    app.Shutdown();
    
    return EXIT_SUCCESS;
}