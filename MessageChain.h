//
// Created by clay on 3/31/23.
//

#ifndef KINOKO_MESSAGECHAIN_H
#define KINOKO_MESSAGECHAIN_H

#include "nlohmann/json.hpp"
#include "TypeDefine.h"

class MessageBlock {
public:
    using Data = nlohmann::json;
    enum class Type {
        AT, REPLY, TEXT, NOT_SUPPORT
    };
    explicit MessageBlock(const nlohmann::json & block)
            : data_(block.at("data")), origin_type_(block.at("type"))
    {
        auto t = block.at("type").get<std::string>();
        auto p = str_type_hash.find(t);
        if(p != str_type_hash.end()) {
            type_ = p->second;
        } else {
            type_ = Type::NOT_SUPPORT;
        }
    }

    [[nodiscard]] const Data& data() const { return data_; }
    [[nodiscard]] Type type() const { return type_; }
    [[nodiscard]] const std::string &originType() const { return origin_type_; }
private:
    static const std::map<std::string, Type> str_type_hash;

    Data data_;
    Type type_;
    std::string origin_type_;
};

class MessageChain {
public:
    [[nodiscard]] const std::vector<MessageBlock> &array() const { return message_chain_; }
    std::vector<MessageBlock> &array() { return message_chain_; }

    [[nodiscard]] bool isAt(Qid self_id) const;
private:
    std::vector<MessageBlock> message_chain_;
};

#endif //KINOKO_MESSAGECHAIN_H
