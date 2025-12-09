cmake_minimum_required(VERSION 3.31)
project(scsdrpc)

include(cmake/discord-rpc.cmake)
include(cmake/scsmodsdk.cmake)

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
)

target_link_libraries(scsdrpc PRIVATE
        DiscordSdk
)