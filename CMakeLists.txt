project(atri)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(UNOFFICIAL_LINK_LIST
        cpr::cpr
        nlohmann_json::nlohmann_json)
set(SOURCE_LIST
        main.cpp
        dependency.h
        TestChat.h
        OpenAI_API/OpenAI_API.cpp OpenAI_API/OpenAI_API.h
        ChatBot/ChatBot.cpp ChatBot/ChatBot.h
        ChatBot/ChatCache.cpp ChatBot/ChatCache.h
        ChatBot/CompletionParameter.cpp ChatBot/CompletionParameter.h
        ChatBot/ChatMemory.cpp ChatBot/ChatMemory.h
        )

add_executable(atri ${SOURCE_LIST})
target_link_libraries(atri PRIVATE ${UNOFFICIAL_LINK_LIST})

add_executable(test ${SOURCE_LIST})
target_link_libraries(test PRIVATE ${UNOFFICIAL_LINK_LIST})
