//
// Created by clay on 3/30/23.
//

#ifndef KINOKO_MESSAGEEVENT_H
#define KINOKO_MESSAGEEVENT_H

#include <nlohmann/json.hpp>
#include "TypeDefine.h"
#include "MessageChain.h"

class MessageEvent {
public:
    explicit MessageEvent(const nlohmann::json& raw_event);
    enum class Type {
        PRIVATE_MESSAGE, GROUP_MESSAGE, NOT_SUPPORT
    };

    [[nodiscard]] Type eventType() const { return message_event_type; }
    [[nodiscard]] Type subType() const { return sub_type; }

    [[nodiscard]] MessageId messageId() const { return message_id; }
    [[nodiscard]] Qid senderId() const { return sender_id; }

    [[nodiscard]] const MessageChain &messageChain() const { return message_chain; }
    [[nodiscard]] const std::string &rawMessage() const { return raw_message; }

    [[nodiscard]] FontType font() const { return font_; }

    [[nodiscard]] const Qinfo &senderInfo() const { return sender_info; }

    [[nodiscard]] const nlohmann::json &rawEvent() const { return raw_event_; }

private:
    Type message_event_type;
    Type sub_type;

    MessageId message_id;
    Qid sender_id;              // "user_id"

    MessageChain message_chain; // "message"
    std::string raw_message;

    FontType font_;
    Qinfo sender_info;          // "sender"

    // in GroupMessageEvent
    // bool at_me;
    // bool reply_me;   // it's so hard

    nlohmann::json raw_event_;
};
class PrivateMessageEvent : MessageEvent {
public:

private:
    Qid target_id_;
};
class GroupMessageEvent : MessageEvent {
public:

private:
    Qid group_id_;
};

#endif //KINOKO_MESSAGEEVENT_H
