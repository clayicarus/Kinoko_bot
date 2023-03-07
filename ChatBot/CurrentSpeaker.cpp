//
// Created by clay on 3/7/23.
//

#include "CurrentSpeaker.h"
#include "../Logger.h"
#include <algorithm>

bool CurrentSpeaker::insert(std::string_view speaker)
{
    LOG_DEBUG("CurrentSpeaker insert");
    if(find(speaker) != q.cend()) {
        return false;
    }
    if(q.size() + 1 > max_size_) {
        q.pop_front();
    }
    q.emplace_back(speaker);
    return true;
}

unsigned long CurrentSpeaker::erase(std::string_view speaker)
{
    SpeakerQueue::iterator i;
    if((i = find(speaker)) != q.end()) {
        q.erase(i);
        return 1;
    }
    return 0;
}

CurrentSpeaker::SpeakerQueue::const_iterator CurrentSpeaker::find(std::string_view speaker) const
{
    return std::find(q.cbegin(), q.cend(), speaker);
}

CurrentSpeaker::SpeakerQueue::iterator CurrentSpeaker::find(std::string_view speaker)
{
    return std::find(q.begin(), q.end(), speaker);
}
