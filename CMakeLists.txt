project(atri)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
set(UNOFFICIAL_LINK_LIST
        cpr::cpr
        nlohmann_json::nlohmann_json)

add_executable(atri main.cpp
        OpenAI_API/OpenAI_API.cpp OpenAI_API/OpenAI_API.h
        dependency.h
        TestChat.cpp TestChat.h)
target_link_libraries(atri PRIVATE ${UNOFFICIAL_LINK_LIST})

add_executable(test test.cpp
        OpenAI_API/OpenAI_API.cpp OpenAI_API/OpenAI_API.h
        dependency.h
        TestChat.cpp TestChat.h)
target_link_libraries(test PRIVATE ${UNOFFICIAL_LINK_LIST})