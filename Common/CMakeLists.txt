set (INC_DIR include)
set (SRC_DIR src)

set (BASE_MODULE
    ${INC_DIR}/Common/Base/ShareContextBase.h
    ${INC_DIR}/Common/Base/ShareContainer.h
    ${INC_DIR}/Common/Base/AnString.h
    ${SRC_DIR}/Base/AnString.cpp
)

set (LOGGER_MODULE
    ${INC_DIR}/Common/Logger/ObserverSink.h
    ${INC_DIR}/Common/Logger/ILogObserver.h

    ${INC_DIR}/Common/Logger/GUIConsole.h
    ${SRC_DIR}/Logger/GUIConsole.cpp

    ${INC_DIR}/Common/Logger/FileLogObserver.h
    ${SRC_DIR}/Logger/FileLogObserver.cpp

    ${INC_DIR}/Common/Logger/LogManager.h
    ${SRC_DIR}/Logger/LogManager.cpp
)

set(DTO
    ${INC_DIR}/Common/DTO/LogMessage.h
)

set(ALL_CORE_SOURCES
    ${INC_DIR}/Common/Config.h
    ${LOGGER_MODULE}
    ${BASE_MODULE}
    ${DTO}
)

antutu_add_module(AntutuCommon
    TYPE SHARED
    SOURCES
        ${ALL_CORE_SOURCES}
    PUBLIC_LIBS
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