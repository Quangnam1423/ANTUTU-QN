set (INC_DIR include)
set (SRC_DIR src)

set (BASE_MODULE
    ${INC_DIR}/Common/Base/ShareContextBase.h
    ${INC_DIR}/Common/Base/ShareContainer.h
    ${INC_DIR}/Common/Base/AnString.h
    ${SRC_DIR}/Base/AnString.cpp
)

set (LOGGER_MODULE
    ${INC_DIR}/Common/Logger/LogMessage.h
    ${SRC_DIR}/Logger/LogMessage.cpp
)

set(ALL_CORE_SOURCES
    ${INC_DIR}/Common/Config.h
    ${LOGGER_MODULE}
    ${BASE_MODULE}
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