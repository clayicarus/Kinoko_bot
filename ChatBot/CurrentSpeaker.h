//
// Created by clay on 3/7/23.
//

#ifndef ATRI_CURRENTSPEAKER_H
#define ATRI_CURRENTSPEAKER_H


#include <string>
#include <deque>

class CurrentSpeaker {
    typedef std::deque<std::string> SpeakerQueue;
public:
    explicit CurrentSpeaker(SpeakerQueue::size_type max_size)
        : max_size_(max_size) {}

    [[nodiscard]] SpeakerQueue::size_type size() const { return q.size(); }

    bool insert(std::string_view speaker);
    SpeakerQueue::size_type erase(std::string_view speaker);

    SpeakerQueue::iterator find(std::string_view speaker);
    [[nodiscard]] SpeakerQueue::const_iterator find(std::string_view speaker) const;
    [[nodiscard]] SpeakerQueue::const_iterator cbegin() const { return q.cbegin(); }
    [[nodiscard]] SpeakerQueue::const_iterator cend() const { return q.cend(); }
private:
    SpeakerQueue q;
    SpeakerQueue::size_type max_size_;
};


#endif //ATRI_CURRENTSPEAKER_H
