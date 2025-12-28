# ---------------------------------------------------------------------------
# Antutu Vulkan Engine - Build Script
# ---------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. Định nghĩa danh sách file (Sử dụng đường dẫn tương đối từ vị trí file CMake này)
set(SOURCES
    "src/ATString.cpp"
    "src/ATNormalMutex.cpp"
    "src/ATSharedMutex.cpp"
)

set(HEADERS
    "include/ATString.h"
    "include/ATConfig.h"
    "include/ATNormalMutex.h"
    "include/ATSharedMutex.h"
)

# 3. Tùy chọn Build: Static hay Shared
# Mặc định là OFF (Build Shared Library .dll/.so)
option(ANTUTU_STATIC "Build Antutu as a static library" OFF)

if(ANTUTU_STATIC)
    add_library(AntutuLib STATIC ${SOURCES} ${HEADERS})
    # Nếu build static, định nghĩa macro ANTUTU_STATIC cho cả thư viện và bên sử dụng (PUBLIC)
    target_compile_definitions(AntutuLib PUBLIC ANTUTU_STATIC)
else()
    add_library(AntutuLib SHARED ${SOURCES} ${HEADERS})
    # Khi build Shared, ta định nghĩa ANTUTU_LIB_EXPORT (PRIVATE) để kích hoạt __declspec(dllexport)
    # Macro này chỉ tồn tại khi đang build nội bộ thư viện.
    target_compile_definitions(AntutuLib PRIVATE ANTUTU_LIB_EXPORT)
endif()

# 4. Cấu hình đường dẫn Include
# Việc sử dụng 'include' giúp bạn có thể dùng #include "ATString.h"
target_include_directories(AntutuLib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 5. Thiết lập Compiler Options cho từng nền tảng
if(MSVC)
    # /W4: Cảnh báo mức cao, /Zi: Tạo file debug, /EHsc: Xử lý ngoại lệ C++
    target_compile_options(AntutuLib PRIVATE /W4 /Zi /EHsc)
    target_link_options(AntutuLib PRIVATE /DEBUG)
else()
    # -Wall -Wextra: Bật tối đa cảnh báo, -g: Giữ symbol debug
    target_compile_options(AntutuLib PRIVATE -Wall -Wextra -g -fPIC)
endif()


add_library(Antutu::AntutuLib ALIAS AntutuLib)