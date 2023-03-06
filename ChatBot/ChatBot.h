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
    ChatBot()
        : scene_("The following is a conversation with an AI assistant. "
                 "The assistant is helpful, creative, clever, and very friendly. "
                 "\n\nHuman: Hello, who are you?\n"
                 "Atri: I am Atri, an AI realized with GPT. How can Atri help you today?\n"
                 "Human: 你可以说中文吗？\n"
                 "Atri: 当然可以，Atri有什么可以帮助您？\n"),
          name_("Atri"),
          cache_(3000)
    {}
    void speak(const std::string &speaker, const std::string &content);
    std::string getOneReply(const std::string &name);

private:
    void setSpeakers(const std::string &speaker);

    typedef std::deque<std::string> MessageQueue;
    MessageQueue messages_;

    ChatCache cache_;

    const std::string name_;
    std::string scene_;
    std::set<std::string> currentSpeaker_;

    CompletionParameter parameter_;
};

#endif //ATRI_CHATBOT_H
