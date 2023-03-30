//
// Created by clay on 3/30/23.
//

#include "MessageEvent.h"
#include "Logger.h"
#include "BotConstant.h"

MessageEvent::MessageEvent(const nlohmann::json &event)
    : raw_message(event["raw_message"]), font_(event["font"]),
      sender_info(event["sender"]), raw_event_(event)
{
    // init var
    auto j = event["message_type"];
    if(j.is_string()) {
        if(j == "private") message_event_type = Type::PRIVATE_MESSAGE;
        else if(j == "group") message_event_type = Type::GROUP_MESSAGE;
        else {
            WARN_LOG("messageHandler - invalid message type " + j.get<std::string>());
            return;
        }
    }
    j = event["sub_type"];
    if(j.is_string()) {
        if(j == "private") sub_type = Type::PRIVATE_MESSAGE;
        else if(j == "group") sub_type = Type::GROUP_MESSAGE;
        else sub_type = Type::NOT_SUPPORT;
    }
    message_id = event["message_id"];
    sender_id = event["user_id"];
    j = event["message"];
    if(!j.is_array()) {
        WARN_LOG("messageHandler - invalid event: message not array");
        return;
    }
    for(const auto& i : j) {
        if(!i.is_object() || !i.contains("data") || !i.contains("type")) {
            WARN_LOG("messageHandler - invalid message_chain");
        }
        message_chain.array().emplace_back(i);
    }
    for(auto i : message_event_paralist) {
        raw_event_.erase(i);
    }
}
