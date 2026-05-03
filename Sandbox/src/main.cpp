#include <ANTUTU/RHI/VulkanInstance.hpp>
#include <Object/Window.hpp>

int main()
{
    Sandbox::Window window(800, 600, "Sandbox Antutu Window");




    // init vulkan instance with config
    att::RHI::VulkanInstance* vulkanInstance;
    att::PlatformInfo::VulkanInstanceConfig config{
        .appName = "Antutu Vulkan Engine",
        .appVer = VK_MAKE_VERSION(1, 0, 0),
        .engineName = "Antutu Engine",
        .engineVer = VK_MAKE_VERSION(1, 0, 0),
        .apiVer = VK_API_VERSION_1_3,
        .exts = {window.GetRequiredExtensions()}
    };

    vulkanInstance = new att::RHI::VulkanInstance();    
    if (!vulkanInstance->Initialize(config)) {
        std::cerr << "Failed to initialize Vulkan instance!" << std::endl;
        return EXIT_FAILURE;
    }
    else 
    {
        std::cout << "Vulkan instance initialized successfully!" << std::endl;
    }

    window.Render();


    // close app
    delete vulkanInstance;
    return EXIT_SUCCESS;
}