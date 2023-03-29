//
// Created by clay on 3/3/23.
//

#include "Roleplay.h"
#include "OpenAI_API/OpenAI_API.h"
#include "base/StringExtra.h"

bool Roleplay::speak(std::string_view content, const Roleplay::MessageCallback& cb)
{
    // TODO: use thread pool
    // TODO: forbidden to call when speaking
    // TODO: success callback and failure callback

    // is safe?
    if(!m_.try_lock()) {
        // is working now
        printf("working now\n");
        return false;
    } else {
        m_.unlock();
    }

    std::string cnt(content);
    auto f = [this, cnt, cb]() {
        // dont capture &cb, cb may destroyed
        // FIXME: when *this destroyed
        std::lock_guard lock(m_);

        // generate and set prompt
        auto talk = toStopFormat(speaker()) + cnt + toStopFormat(botName()); // A: xxx\nB:
        auto prompt = scene() + characterInfo() + cache_.getCacheString(MAX_CACHE_SIZE) + talk;
        parameter_.setPrompt(prompt);
        parameter_.setStop({toStopFormat(speaker()), toStopFormat(botName())});
        // request api for completion
        std::string res;
        auto r = OpenAI_API::createCompletion(parameter_.getPara());
        if(!r["is_error"]) {
            if(r["status_code"] == 200) {
                res = r["response_data"]["choices"][0]["text"];
                StringExtra::trim(res, '\n');
                StringExtra::trim(res, ' ');
                talk.append(res);
                cache_.insert(speaker(), talk);
            } else {
                // LOG_ERROR("API response error");
                res = "[API Error]: " + r["response_data"].dump();
            }
        } else {
            // LOG_ERROR("cpr error");
            std::string err_msg = r["error_message"];
            res = "[Network Error]: " + err_msg;
        }
        cb(res);
    };

    // FIXME: jthread in class Roleplay
    std::thread t(f);
    t.detach();

    return true;
}

bool Roleplay::setSpeaker(std::string_view new_speaker)
{
    // TODO: Update cache
    // TODO: Forbidden to call when speaking
    speaker_ = new_speaker;
    return true;
}

bool Roleplay::setBotName(std::string_view new_name)
{
    // TODO: Update cache
    // TODO: Forbidden to call when speaking
    bot_name_ = new_name;
    return true;
}

bool Roleplay::setCharacterInfo(std::string_view new_set)
{
    // TODO: Update cache
    // TODO: Forbidden to call when speaking
    character_info_ = new_set;
    return true;
}
