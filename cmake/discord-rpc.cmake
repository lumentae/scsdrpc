cmake_minimum_required(VERSION 3.31)
include(FetchContent)

set(CMAKE_CXX_STANDARD 26)

set(DISCORD_SDK_LIB_FOLDER ${CMAKE_BINARY_DIR}/External/DiscordSdk/lib/x86_64)
if(WIN32)
    set(DISCORD_SDK_LIB_PATH ${DISCORD_SDK_LIB_FOLDER}/discord_game_sdk.dll.lib)
else()
    set(DISCORD_SDK_LIB_PATH ${DISCORD_SDK_LIB_FOLDER}/discord_game_sdk.so)
endif()

set(DISCORD_SDK_SRC_PATH ${CMAKE_BINARY_DIR}/External/DiscordSdk/cpp)

FetchContent_Declare(DiscordSdk
        URL "https://dl-game-sdk.discordapp.net/3.2.1/discord_game_sdk.zip"
        SOURCE_DIR ${CMAKE_BINARY_DIR}/External/DiscordSdk
)

FetchContent_MakeAvailable(DiscordSdk)

add_library(DiscordSdk STATIC
        ${DISCORD_SDK_SRC_PATH}/achievement_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/achievement_manager.h
        ${DISCORD_SDK_SRC_PATH}/activity_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/activity_manager.h
        ${DISCORD_SDK_SRC_PATH}/application_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/application_manager.h
        ${DISCORD_SDK_SRC_PATH}/core.cpp
        ${DISCORD_SDK_SRC_PATH}/core.h
        ${DISCORD_SDK_SRC_PATH}/discord.h
        ${DISCORD_SDK_SRC_PATH}/event.h
        ${DISCORD_SDK_SRC_PATH}/ffi.h
        ${DISCORD_SDK_SRC_PATH}/image_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/image_manager.h
        ${DISCORD_SDK_SRC_PATH}/lobby_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/lobby_manager.h
        ${DISCORD_SDK_SRC_PATH}/network_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/network_manager.h
        ${DISCORD_SDK_SRC_PATH}/overlay_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/overlay_manager.h
        ${DISCORD_SDK_SRC_PATH}/relationship_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/relationship_manager.h
        ${DISCORD_SDK_SRC_PATH}/storage_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/storage_manager.h
        ${DISCORD_SDK_SRC_PATH}/store_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/store_manager.h
        ${DISCORD_SDK_SRC_PATH}/types.cpp
        ${DISCORD_SDK_SRC_PATH}/types.h
        ${DISCORD_SDK_SRC_PATH}/user_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/user_manager.h
        ${DISCORD_SDK_SRC_PATH}/voice_manager.cpp
        ${DISCORD_SDK_SRC_PATH}/voice_manager.h
)

target_include_directories(DiscordSdk PUBLIC
        ${DISCORD_SDK_SRC_PATH}
)