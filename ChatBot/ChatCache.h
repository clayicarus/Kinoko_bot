//
// Created by clay on 3/3/23.
//

#ifndef ATRI_CHATCACHE_H
#define ATRI_CHATCACHE_H


#include <string>
#include <deque>

class ChatCache {
    typedef std::string Speaker;
    typedef std::string Content;
    typedef std::deque<std::pair<Speaker, Content>> Cache;  // push_front, pop_back
public:
    const std::string& getPrompt();
    void insert(const Speaker &speaker, const Content &content);

    const Content::size_type &maxPromptSize() const { return maxPromptSize_; }
    Content::size_type &maxPromptSize() { return maxPromptSize_; }

    Content::size_type currentPromptSize() const { return prompt_.size(); }
private:
    Content::size_type maxPromptSize_;
    Cache cache_;
    Content prompt_;

    bool& changed() { return changed_; }
    const bool& changed() const { return changed_; }
    bool changed_;

    void makePrompt();

    void printCurrentPrompt() const { printf("%s", prompt_.c_str()); }
};


#endif //ATRI_CHATCACHE_H
