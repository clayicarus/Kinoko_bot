project(atri)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
link_directories(lib)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(UNOFFICIAL_LINK_LIST
        cpr::cpr
        nlohmann_json::nlohmann_json
        muduo_net
        muduo_base
        pthread
        )
set(SOURCE_LIST
        initKey.cpp

        OpenAI_API/OpenAI_API.cpp

        RoleplayModule/Roleplay.cpp
        RoleplayModule/RoleplayCache.cpp
        OpenAI_API/CompletionParameter.cpp

        WebsocketServer/WebsocketServer.cpp
        WebsocketServer/DataFrameCodec.cpp

        base/HttpParser.cpp
        base/base64.cpp
        base/sha1_portable.cpp
        )

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE ${UNOFFICIAL_LINK_LIST})

add_executable(test test.cpp ${SOURCE_LIST})
target_link_libraries(test PRIVATE ${UNOFFICIAL_LINK_LIST})
