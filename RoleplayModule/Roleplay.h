//
// Created by clay on 3/3/23.
//

#ifndef ATRI_CHAT_H
#define ATRI_CHAT_H

#include <string>
#include <vector>
#include <set>
#include "ChatCache.h"
#include "CompletionParameter.h"
#include "ChatMemory.h"
#include "CurrentSpeaker.h"
#include "ThreadsafeQueue.h"

class Chat {
public:
    Chat()
        : scene_("The following is a conversation with an AI assistant. "
                 "The assistant is helpful, creative, clever, and very friendly. "
                 "\n\nHuman: Hello, who are you?\n"
                 "Atri: I am Atri, an AI realized with GPT. How can Atri help you today?\n"
                 "Human: 你可以说中文吗？\n"
                 "Atri: 当然可以，Atri有什么可以帮助您？\n"),
          name_("Atri"),
          cache_(3000),
          currentSpeaker_(3)
    {}
    void speak(std::string_view speaker, std::string_view content);
    std::string getOneReply(std::string_view name);
    std::string &scene() { return scene_; }
    std::string &name() { return name_; }
private:
    static std::string toStopFormat(std::string_view name) { return '\n' + std::string(name) + ": "; }
    void setSpeakers();

    typedef ThreadsafeQueue<std::string> MessageQueue;
    MessageQueue messages_;

    ChatCache cache_;

    std::string name_;
    std::string scene_;

    CurrentSpeaker currentSpeaker_;
    CompletionParameter parameter_;
};

#endif //ATRI_CHAT_H
