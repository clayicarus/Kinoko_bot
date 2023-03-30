//
// Created by clay on 3/30/23.
//

#include "MessageChain.h"

const std::map<std::string, MessageBlock::Type> MessageBlock::str_type_hash = {
        {"at",    MessageBlock::Type::AT}, {"text", MessageBlock::Type::TEXT},
        {"reply", MessageBlock::Type::REPLY}
};

bool MessageChain::isAt(Qid self_id) const {
    for(const MessageBlock &i : message_chain_) {
        if(i.type() == MessageBlock::Type::AT
           && self_id == std::stoll(i.data().at("qq").get<std::string>())) {
            return true;
        }
    }
    return false;
}
