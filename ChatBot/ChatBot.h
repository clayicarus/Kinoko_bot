//
// Created by clay on 3/3/23.
//

#ifndef ATRI_CHATBOT_H
#define ATRI_CHATBOT_H

#include <string>
#include <vector>
#include "ChatCache.h"
#include "CompletionParameter.h"

class CompletionParameter;
class ChatCache;

class ChatBot {
public:
    std::string speakAndResponse();

private:
    ChatCache cache;
    CompletionParameter parameter;
    std::string scene;
    std::vector<std::string> role;
    std::string botName;

};

#endif //ATRI_CHATBOT_H
