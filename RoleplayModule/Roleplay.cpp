//
// Created by clay on 3/3/23.
//

#include "Roleplay.h"
#include "OpenAI_API/OpenAI_API.h"

bool Roleplay::speak(std::string_view content, const Roleplay::MessageCallback& cb)
{
    // TODO: use thread pool
    // TODO: forbidden to call when speaking
    // TODO: success callback and failure callback

    if(working_) {
        // is working now
        return false;
    }

    std::string cnt(content);
    auto f = [this, cnt, cb]() {
        // dont capture &cb, cb may destroyed
        // FIXME: when *this destroyed
        working_ = true;

        // generate and set prompt
        auto talk = toStopFormat(speaker()) + cnt + toStopFormat(name()); // A: xxx\nB:
        auto prompt = scene_ + cache_.getCacheString(MAX_CACHE_SIZE) + talk;
        parameter_.setPrompt(prompt);
        parameter_.setStop({toStopFormat(speaker()), toStopFormat(name())});
        // request api for completion
        std::string res;
        auto r = OpenAI_API::createCompletion(parameter_.getPara());
        if(!r["is_error"]) {
            if(r["status_code"] == 200) {
                res = r["response_data"]["choices"][0]["text"];
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

        working_ = false;
    };

    std::thread t(f);
    t.detach();

    return true;
}

bool Roleplay::setSpeaker(std::string_view new_speaker)
{
    // TODO: Update cache, forbidden to call when speaking
    speaker_ = new_speaker;
    return true;
}

bool Roleplay::setName(std::string_view new_name)
{
    // TODO: Update cache, forbidden to call when speaking
    name_ = new_name;
    return true;
}

bool Roleplay::setScene(std::string_view new_scene)
{
    // TODO: Clean cache, forbidden to call when speaking
    scene_ = new_scene;
    return true;
}
