include(FetchContent)

set(SCS_MOD_SDK_INCLUDE_PATH ${CMAKE_BINARY_DIR}/external/scsmodsdk/include)

FetchContent_Declare(scsmodsdk
        URL "https://download.eurotrucksimulator2.com/scs_sdk_1_14.zip"
        SOURCE_DIR ${CMAKE_BINARY_DIR}/external/scsmodsdk
)

FetchContent_MakeAvailable(scsmodsdk)