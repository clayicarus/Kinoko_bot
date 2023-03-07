//
// Created by clay on 3/3/23.
//

#include <cassert>
#include "ChatCache.h"
#include "../Logger.h"

void ChatCache::insert(std::string_view speaker, std::string_view talk)
{
    // <= max_size
    // FIXME: talk.size() > maxCacheSize_
    LOG_DEBUG("insert speaker and talk");
    while(talk.size() + currCacheSize_ > maxCacheSize_) {
        LOG_DEBUG("cache size full");
        currCacheSize_ -= cache_.back().second.size();
        cache_.pop_front();
    }
    LOG_DEBUG("cache updated");
    cache_.emplace_back(speaker, talk);
    currCacheSize_ += talk.size();
}

std::string ChatCache::getCacheString(unsigned long max_size) const
{
    Talk::size_type cur_sz = 0;
    std::string res;
    for(const auto &i : cache_) {
        if(cur_sz + i.second.size() <= max_size)
            res.append(i.second);
        else
            break;
    }
    LOG_DEBUG("cache string get");
    return res;
}
