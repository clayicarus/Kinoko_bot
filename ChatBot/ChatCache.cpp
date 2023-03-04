//
// Created by clay on 3/3/23.
//

#include <cassert>
#include "ChatCache.h"

const std::string &ChatCache::getPrompt()
{
    if(promptChanged()) {
        makePrompt();
    }
    return prompt_;
}

void ChatCache::makePrompt()
{
    Content::size_type curSz = 0;
    Content res;
    promptChanged_ = false;
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
    // TODO: Cache class, Prompt class, divide operation
    while(content.size() + currentCacheSize() > maxPromptSize()) {
        assert(!cache_.empty());    // FIXME: content.size() > maxPromptSize()
        currCacheSize_ -= cache_.back().second.size();
        cache_.pop_back();
        promptChanged_ = true;
    }
    cache_.emplace_front(speaker, content);
    if(!promptChanged()) {
        prompt_.append(content);
    }
}
