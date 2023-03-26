project(atri)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-fsanitize=address)
link_libraries(-fsanitize=address)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(UNOFFICIAL_LINK_LIST
        cpr::cpr
        nlohmann_json::nlohmann_json
        )
set(SOURCE_LIST
        initKey.cpp
        TestChat.h
        OpenAI_API/OpenAI_API.cpp OpenAI_API/OpenAI_API.h
        Chat/Chat.cpp Chat/Chat.h
        Chat/ChatCache.cpp Chat/ChatCache.h
        Chat/CompletionParameter.cpp Chat/CompletionParameter.h
        Chat/ChatMemory.cpp Chat/ChatMemory.h
        Logger.cpp Logger.h Chat/CurrentSpeaker.cpp Chat/CurrentSpeaker.h Chat/ThreadsafeQueue.h)

add_executable(atri main.cpp ${SOURCE_LIST})
target_link_libraries(atri PRIVATE ${UNOFFICIAL_LINK_LIST})

add_executable(test test.cpp ${SOURCE_LIST})
target_link_libraries(test PRIVATE ${UNOFFICIAL_LINK_LIST})
