//
// Created by clay on 3/3/23.
//

#ifndef ATRI_ROLEPLAY_H
#define ATRI_ROLEPLAY_H

#include <string>
#include <vector>
#include <set>
#include <atomic>
#include "RoleplayCache.h"
#include "CompletionParameter.h"

class Roleplay {
    static constexpr int MAX_CACHE_SIZE = 3000;
public:
    Roleplay()
        : scene_("以下是与AI助理的一段对话。它十分能干、聪慧、具有创造性，而且待人十分友善。\n"),
          speaker_("Human"),
          name_("Atri"),
          cache_(MAX_CACHE_SIZE),
          working_(false)
    {}
    typedef std::function<void(const std::string &)> MessageCallback;
    bool speak(std::string_view content, const MessageCallback& cb);
    [[nodiscard]] const std::string &scene() const { return scene_; }
    [[nodiscard]] const std::string &name() const { return name_; }
    [[nodiscard]] const std::string &speaker() const { return speaker_; }
    bool setSpeaker(std::string_view new_speaker);
    bool setName(std::string_view new_name);
    bool setScene(std::string_view new_scene);


private:
    static std::string toStopFormat(std::string_view name) { return '\n' + std::string(name) + ": "; }

    std::string speaker_;
    std::string name_;
    std::string scene_;
    RoleplayCache cache_;
    CompletionParameter parameter_;

    std::atomic<bool> working_;
};

#endif //ATRI_ROLEPLAY_H
