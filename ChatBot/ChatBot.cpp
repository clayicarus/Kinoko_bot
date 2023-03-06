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
    res = res.substr(name.size() + strlen(": "));
    return res;
}

void ChatBot::speak(const std::string &speaker, const std::string &content)
{
    auto talk = speaker + ": " + content + "\n";
    auto prompt = scene_ + cache_.getCacheString(3000) + talk;
    setSpeakers(speaker);
    parameter_.setPrompt(prompt);

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

void ChatBot::setSpeakers(const std::string &speaker)
{
    auto temp(speaker);
    temp.push_back('\n');
    temp = "\n" + temp + ": ";
    auto self = "\n" + name_ + ": ";
    parameter_.setStop({self, temp});
}

