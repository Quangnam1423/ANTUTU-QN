file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h" "include/*.hpp")

add_library(MyLibrary SHARED ${SOURCES} ${HEADERS})

target_include_directories(MyLibrary PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if(MSVC)
    target_compile_options(MyLibrary PRIVATE /Zi)
    target_link_options(MyLibrary PRIVATE /DEBUG)
else()
    target_compile_options(MyLibrary PRIVATE -g)
endif()

target_compile_definitions(MyLibrary PRIVATE MY_LIB_EXPORT_LOGIC)