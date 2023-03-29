//
// Created by clay on 3/3/23.
//

#ifndef ATRI_ROLEPLAY_H
#define ATRI_ROLEPLAY_H

#include <string>
#include <mutex>
#include "RoleplayCache.h"
#include "OpenAI_API/CompletionParameter.h"

class Roleplay {
    static constexpr int MAX_CACHE_SIZE = 3000;
public:
    Roleplay(const Roleplay &) = delete;
    Roleplay& operator=(const Roleplay &) = delete;
    // move ctor?

    explicit Roleplay(std::string_view bot_name, std::string_view speaker_name,
                      std::string_view character_info = "它是一个AI助理，十分聪慧、讲话具有创造性，而且待人友善。\n")
        : speaker_(speaker_name),
          bot_name_(bot_name),
          cache_(MAX_CACHE_SIZE),
          character_info_(character_info),
          scene_("以下是与" + bot_name_ + "的一段对话。\n")
    {}
    // FIXME: detach thread
    ~Roleplay() = default;

    typedef std::function<void(const std::string &)> MessageCallback;
    bool speak(std::string_view content, const MessageCallback& cb);

    [[nodiscard]] const std::string &botName() const { return bot_name_; }
    [[nodiscard]] const std::string &speaker() const { return speaker_; }
    [[nodiscard]] const std::string &characterInfo() const { return character_info_; }
    bool setSpeaker(std::string_view new_speaker);
    bool setBotName(std::string_view new_name);
    bool setCharacterInfo(std::string_view new_set);

private:
    static std::string toStopFormat(std::string_view name) { return '\n' + std::string(name) + ": "; }

    [[nodiscard]] const std::string &scene() const { return scene_; }

    // prompt elements, prompt = scene + character + talk
    std::string speaker_;
    std::string bot_name_;
    std::string scene_;
    std::string character_info_;
    // message record
    RoleplayCache cache_;
    CompletionParameter parameter_;
    // thread
    std::mutex m_;
};

#endif //ATRI_ROLEPLAY_H
