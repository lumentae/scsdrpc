cmake_minimum_required(VERSION 3.31)
project(scsdrpc)

message("Configuring project: ${PROJECT_NAME}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 26)

message("Fetching Discord SDK...")
include(cmake/discord-rpc.cmake)

message("Fetching SCS Mod SDK...")
include(cmake/scsmodsdk.cmake)

message("Fetching spdlog...")
include(cmake/spdlog.cmake)

file(GLOB_RECURSE SRC_FILES
        CONFIGURE_DEPENDS
        src/*.cpp
        src/*.c
        src/*.hpp
        src/*.h
)

add_library(scsdrpc SHARED ${SRC_FILES})

target_include_directories(scsdrpc PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${DISCORD_SDK_INCLUDE_PATH}
        ${SCS_MOD_SDK_INCLUDE_PATH}
        ${spdlog_SOURCE}
)

target_link_libraries(scsdrpc PRIVATE
        DiscordSdk
        spdlog::spdlog
)

set_target_properties(scsdrpc PROPERTIES
        BUILD_RPATH "$ORIGIN"
        INSTALL_RPATH "$ORIGIN"
)

install(
        TARGETS scsdrpc
        LIBRARY DESTINATION "${GAME_INSTALL_PATH}/plugins"
)