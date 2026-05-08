set (INC_DIR include)
set (SRC_DIR src)

set(ALL_CORE_SOURCES
    ${INC_DIR}/Common/Config.h
)

antutu_add_module(AntutuCommon
    TYPE STATIC
    SOURCES
        ${ALL_CORE_SOURCES}
    LINK_LIBS
        spdlog
)


target_compile_definitions(AntutuCommon PRIVATE COMMON_CORE_EXPORT)


target_include_directories(AntutuCommon 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${INC_DIR}>
        $<INSTALL_INTERFACE:include/Common>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${SRC_DIR}
) 