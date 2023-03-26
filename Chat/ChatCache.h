//
// Created by clay on 3/3/23.
//

#ifndef ATRI_CHATCACHE_H
#define ATRI_CHATCACHE_H


#include <string>
#include <deque>
#include "ChatMemory.h"

class ChatCache {
    typedef std::string Speaker;
    typedef std::string Talk;
    typedef std::deque<std::pair<Speaker, Talk>> Cache;  // push_back, pop_front
public:
    explicit ChatCache(Talk::size_type cache_size)
        : maxCacheSize_(cache_size), currCacheSize_(0)
    {}

    [[nodiscard]] std::string getCacheString(Talk::size_type max_size) const;
    void insert(std::string_view speaker, std::string_view talk);

    [[nodiscard]] const Talk::size_type &currentCacheSize() const { return currCacheSize_; }
private:
    Talk::size_type maxCacheSize_;
    Talk::size_type currCacheSize_;
    Cache cache_;
    ChatMemory mem_;
};


#endif //ATRI_CHATCACHE_H
