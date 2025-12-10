cmake_minimum_required(VERSION 3.31)
project(scsdrpc)

message("Configuring project: ${PROJECT_NAME}")

message("Fetching Discord SDK...")
include(cmake/discord-rpc.cmake)

message("Fetching SCS Mod SDK...")
include(cmake/scsmodsdk.cmake)

message("Fetching spdlog...")
include(cmake/spdlog.cmake)

set(CMAKE_CXX_STANDARD 26)

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

install(
        TARGETS scsdrpc
        LIBRARY DESTINATION "${GAME_INSTALL_PATH}/plugins"
)