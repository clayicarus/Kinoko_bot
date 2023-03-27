//
// Created by clay on 3/3/23.
//

#include <cassert>
#include "RoleplayCache.h"

void RoleplayCache::insert(std::string_view speaker, std::string_view talk)
{
    // <= max_size
    // FIXME: talk.size() > maxCacheSize_
    while(talk.size() + currCacheSize_ > maxCacheSize_) {
        currCacheSize_ -= cache_.back().second.size();
        cache_.pop_front();
    }
    cache_.emplace_back(speaker, talk);
    currCacheSize_ += talk.size();
}

std::string RoleplayCache::getCacheString(unsigned long max_size) const
{
    Talk::size_type cur_sz = 0;
    std::string res;
    for(const auto &i : cache_) {
        if(cur_sz + i.second.size() <= max_size)
            res.append(i.second);
        else
            break;
    }
    return res;
}
