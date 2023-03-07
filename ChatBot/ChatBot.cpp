//
// Created by clay on 3/3/23.
//

#include "ChatBot.h"
#include "../OpenAI_API/OpenAI_API.h"
#include "../Logger.h"

std::string ChatBot::getOneReply(const std::string &name)
{
    if(messages_.empty()) {
        LOG_FATAL("MessageQueue empty");
    }
    auto res = messages_.back();
    messages_.pop_back();
    return res;
}

void ChatBot::speak(std::string_view speaker, std::string_view content)
{
    // generate and set prompt
    auto talk = std::string(speaker) + ": " + std::string(content) + "\n" + name_ + ": "; // A: xxx\nB:
    auto prompt = scene_ + cache_.getCacheString(3000) + talk;
    parameter_.setPrompt(prompt);
    // insert and set speakers
    currentSpeaker_.insert(speaker);
    setSpeakers();
    // request api for completion
    std::string res;
    LOG_INFO("createCompletion");
    auto r = OpenAI_API::createCompletion(parameter_.getPara());
    LOG_INFO("createCompletion finished");
    if(!r["is_error"]) {
        if(r["status_code"] == 200) {
            res = r["response_data"]["choices"][0]["text"];
            talk.append(res + '\n');
            cache_.insert(speaker, talk);
        } else {
            LOG_ERROR("API response error");
            res = "[API Error]: " + r["response_data"].dump();
        }
    } else {
        LOG_ERROR("cpr error");
        std::string err_msg = r["error_message"];
        res = "[Network Error]: " + err_msg;
    }
    messages_.push_front(res);
}

void ChatBot::setSpeakers()
{
    auto b = currentSpeaker_.cbegin();
    auto e = currentSpeaker_.cend();
    std::vector<std::string> res;
    while(b != e) {
        auto temp = toStopFormat(*b++);
        res.emplace_back(temp);
    }
    res.emplace_back(toStopFormat(name()));
    LOG_DEBUG("set speaker");
    parameter_.setStop(res);
}

