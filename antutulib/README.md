# Antutu Vulkan Engine - Core Library

![Standard](https://img.shields.io/badge/Standard-C%2B%2B17-blue.svg?style=flat&logo=c%2B%2B)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-lightgrey.svg?style=flat&logo=linux&logoColor=white)
![License](https://img.shields.io/badge/License-GPLv3-green.svg?style=flat)
![Build Status](https://img.shields.io/badge/Build-Passing-brightgreen.svg)

**AntutuLib** is the fo undational core library for the **Antutu Vulkan Engine**. It provides a robust, cross-platform abstraction layer for system-level operations, including optimized string handling, thread synchronization primitives, and platform configuration.

Developed with **Modern C++ (C++17)**, it is designed to be lightweight, fast, and easily integrable into other projects via CMake.

---

## 📑 Table of Contents
- [Features](#-features)
- [Directory Structure](#-directory-structure)
- [Prerequisites](#-prerequisites)
- [Building the Library](#-building-the-library)
- [Integration Guide](#-integration-guide)
- [Usage Example](#-usage-example)
- [License](#-license)

---

## 🚀 Features

* **Cross-Platform Architecture**: Seamlessly supports **Windows (MSVC)** and **Linux (GCC/Clang)** via smart macro detection (`ATConfig.h`).
* **ATString**: A custom, high-performance string manipulation class tailored for engine usage.
* **Threading Primitives**:
    * `ATNormalMutex`: Standard wrapper for mutual exclusion.
    * `ATSharedMutex`: Efficient Read-Write lock implementation for high-concurrency scenarios.
* **Flexible Linking**: Supports both **Shared (DLL/SO)** and **Static (LIB/A)** build modes.
* **Modern CMake**: Exports targets with namespace support (`Antutu::AntutuLib`).

---

## 📁 Directory Structure

```text
AntutuVulkanEngine/
├── antutulib/
│   ├── include/          # Public headers (ATString.h, ATConfig.h, etc.)
│   └── src/              # Implementation files (.cpp)
├── test/                 # Unit tests and usage examples
├── CMakeLists.txt        # Main build script
└── README.md             # Documentation