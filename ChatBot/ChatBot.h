//
// Created by clay on 3/3/23.
//

#ifndef ATRI_CHATBOT_H
#define ATRI_CHATBOT_H

#include <string>
#include <vector>
#include <set>
#include "ChatCache.h"
#include "CompletionParameter.h"
#include "ChatMemory.h"

class CompletionParameter;
class ChatCache;

class ChatBot {
public:
    ChatBot();
    void speak(const std::string &name, const std::string &content);
    std::string&& getOneReply(const std::string &name);

private:
    ChatCache cache;
    ChatMemory memory;

    const std::string botName;
    std::string scene;
    std::set<std::string> currentSpeaker;

    CompletionParameter parameter;
    std::string debugResponse;
};

#endif //ATRI_CHATBOT_H
