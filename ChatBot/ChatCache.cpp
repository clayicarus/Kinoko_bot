//
// Created by clay on 3/3/23.
//

#include "ChatCache.h"

const std::string &ChatCache::getPrompt()
{
    if(changed()) {
        makePrompt();
    }
    return prompt_;
}

void ChatCache::makePrompt()
{
    Content::size_type curSz = 0;
    Content res;
    for(const auto &i : cache_) {
        if(i.second.size() + curSz <= maxPromptSize()) {
            curSz += i.second.size();
            res.append(i.second);
        } else {
            return;
        }
    }
}

void ChatCache::insert(const ChatCache::Speaker &speaker, const ChatCache::Content &content)
{
    cache_.emplace_front(speaker, content);
    if(content.size() + currentPromptSize() > maxPromptSize()) {
        changed() = true;
    } else {
        prompt_.append(content);
    }
}
