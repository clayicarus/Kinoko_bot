//
// Created by clay on 3/3/23.
//

#ifndef ATRI_ROLEPLAYCACHE_H
#define ATRI_ROLEPLAYCACHE_H

#include <string>
#include <deque>

class RoleplayCache {
    typedef std::string Speaker;
    typedef std::string Talk;
    typedef std::deque<std::pair<Speaker, Talk>> Cache;  // push_back, pop_front
public:
    explicit RoleplayCache(Talk::size_type cache_size)
        : max_cache_size_(cache_size), curr_cache_size_(0)
    {}

    [[nodiscard]] std::string getCacheString(Talk::size_type max_size) const;
    void insert(std::string_view speaker, std::string_view talk);

    [[nodiscard]] const Talk::size_type &currentCacheSize() const { return curr_cache_size_; }
private:
    Talk::size_type max_cache_size_;
    Talk::size_type curr_cache_size_;
    Cache cache_;
};


#endif //ATRI_ROLEPLAYCACHE_H
