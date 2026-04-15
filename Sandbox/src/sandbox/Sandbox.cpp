#include "sandbox/Sandbox.hpp"
#include <window/Window.hpp>
#include <ANTUTU/System/Logger.hpp>

// SandBox::SandBox()
// {
//     Init();
// }

// SandBox::~SandBox()
// {
//     delete m_window;
//     m_logger->WriteLog(att::System::ModuleName::MODULE_APPLICATION, 
//         att::System::LogLevel::LOG_INFO, 
//         "Sandbox destroyed.");
// }

// void SandBox::Init()
// {
//     m_logger = std::make_shared<att::System::Logger>("SandBox");
//     m_window = new Antutu::Window();

//     m_logger->WriteLog(att::System::ModuleName::MODULE_APPLICATION, 
//         att::System::LogLevel::LOG_INFO, 
//         "Sandbox initialized."
//     );
// }

// void SandBox::Run()
// {
//     m_logger->WriteLog(att::System::ModuleName::MODULE_APPLICATION, 
//         att::System::LogLevel::LOG_INFO, 
//         "Sandbox running."
//     );

//     while (!m_window->ShouldClose()) {
//         m_window->PollEvents();
//         // Update and Render logic would go here
//     }
// }

// void SandBox::Terminate()
// {
//     m_logger->WriteLog(att::System::ModuleName::MODULE_APPLICATION, 
//         att::System::LogLevel::LOG_INFO, 
//         "Sandbox terminating."
//     );
//     // Additional termination logic can be added here
// }


// void SandBox::Exit()
// {
//     m_logger->WriteLog(att::System::ModuleName::MODULE_APPLICATION, 
//         att::System::LogLevel::LOG_INFO, 
//         "Exiting Sandbox."
//     );
//     // Additional exit logic can be added here
// }