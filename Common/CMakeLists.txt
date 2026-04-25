set (INC_DIR include)
set (SRC_DIR src)

set(ALL_CORE_SOURCES

)

antutu_add_module(AntutuCommon
    TYPE STATIC
    SOURCES
        ${ALL_CORE_SOURCES}
    LINK_LIBS
        AntutuCore
)


target_compile_definitions(AntutuCommon PRIVATE ANTUTU_COMMON_EXPORT)


target_include_directories(AntutuCommon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    
)