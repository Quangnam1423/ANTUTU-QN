# Antutu Vulkan Angine

- 3D Graphics Engine based on Vulkan.

## Init dependencies Installation - Dependencies for Linux (Ubuntu)

Before building the VulKan Game Engine, make sure your system has all requireed development package installed.
Run the following commands in your terminal:

```bash
# --- Update system packages ---
sudo apt update && sudo apt upgrade -y
# --- Essential build tools ---
sudo apt install -y vulkan-tools vulkan-validationlayers-dev libvulkan-dev

# --- GLFW (for window creation and input) ---
sudo apt install -y libglfw3-dev

# --- GLM (math library for 3D transformations) ---
sudo apt install -y libglm-dev

# --- STB image loader (header-only, can be manually added) ---
```

## Compile and Run

```bash
mkdir -p out/builds
cmake -S . -B out/build
cd out/build
make
```
## Folder & Structure

```

Antutu/
│
├── CMakeLists.txt
├── README.md
│
├── engine/                         # Core engine logic (cross-platform)
│   ├── Core/
│   │   ├── Application.hpp/.cpp    # App base class
│   │   ├── Engine.hpp/.cpp         # Engine main loop
│   │   ├── Event.hpp/.cpp          # Event system 
│   │   ├── Logger.hpp/.cpp         # Logging utilities
│   │   ├── Time.hpp/.cpp           # Time, deltaTime
│   │   └── Config.hpp/.cpp         # App configuration loader
│   │
│   ├── Platform/
│   │   ├── GLFWWindow.hpp/.cpp     # GLFW-based window
│   │   ├── VulkanContext.hpp/.cpp  # Vulkan init / surface
│   │   ├── Input.hpp/.cpp          # Keyboard, mouse handler
│   │   └── FileSystem.hpp/.cpp     # Cross-platform path/IO
│   │
│   ├── Graphics/
│   │   ├── Renderer.hpp/.cpp       # High-level renderer
│   │   ├── RenderAPI.hpp/.cpp      # Abstract API (GL/Vulkan/Metal)
│   │   ├── Vulkan/                 # Vulkan-specific
│   │   │   ├── VulkanInstance.hpp/.cpp
│   │   │   ├── VulkanDevice.hpp/.cpp
│   │   │   ├── VulkanSwapchain.hpp/.cpp
│   │   │   └── VulkanPipeline.hpp/.cpp
│   │   └── Resources/              # Shaders, materials, textures
│   │
│   ├── Scene/
│   │   ├── Entity.hpp/.cpp         # Entity-component
│   │   ├── Component.hpp/.cpp      # Transform, Mesh, Camera
│   │   ├── Scene.hpp/.cpp          # Scene graph
│   │   └── Systems/                # ECS systems
│   │
│   ├── Scripting/
│   │   ├── LuaVM.hpp/.cpp
│   │   ├── ScriptManager.hpp/.cpp
│   │   └── API/                    # Binding C++ ↔ Lua
│   │
│   └── IPC/
│       ├── IPCManager.hpp/.cpp     # Abstract IPC interface
│       ├── Message.hpp/.cpp        # Message struct
│       └── Transport/              # Implementation (Socket, Pipe)
│           ├── SocketIPC.hpp/.cpp
│           └── JSONRPC.hpp/.cpp
│
├── editor/                         # GUI Editor (Qt/ImGui)
│   ├── EditorApp.hpp/.cpp          # Entry for editor
│   ├── Dockspace.hpp/.cpp          # ImGui window management
│   ├── Panels/                     # Scene, Inspector, Console...
│   │   ├── ScenePanel.hpp/.cpp
│   │   ├── InspectorPanel.hpp/.cpp
│   │   └── ConsolePanel.hpp/.cpp
│   └── Resources/                  # Icons, styles
│
├── tools/                          # External tools / processes
│   ├── ShaderCompiler/             # Shader compile subprocess
│   ├── AssetProcessor/             # Asset import/conversion process
│   └── ScriptRunner/               # Script execution process
│
├── runtime/                        # Player / game runtime (built from engine)
│   ├── Main.cpp                    # Entry for runtime executable
│   └── GameLayer.hpp/.cpp
│
├── third_party/
│   ├── glfw/
│   ├── glad/
│   ├── glm/
│   ├── imgui/
│   ├── spdlog/
│   ├── json/
│   └── zeromq/
│
└── assets/
    ├── shaders/
    ├── models/
    ├── textures/
    ├── scripts/
    └── scenes/
```

## RoadMap

``` road map
1. editor/EditorApp.cpp (main.cpp): this file con
2. create VulkanInstance to manage VkInstance
    2.1 VkInstance: manager global condition, extension, validation layers.
    2.2 VkSurfaceKHR: stand for surface window connect Vulkan to GLFWwindow.
    2.3 VkPhysicalDevice: stand for physics graphics card (GPU).
    2.4 VkDevice: Stande for logical device, main UI for command GPU.

```