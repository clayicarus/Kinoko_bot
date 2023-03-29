//
// Created by clay on 3/2/23.
//

#include "RoleplayModule/Roleplay.h"
#include "OpenAI_API/OpenAI_API.h"
#include "WebsocketServer/WebsocketServer.h"
#include "muduo/net/EventLoop.h"
#include "Logger.h"
#include "base/StringExtra.h"

#include <nlohmann/json.hpp>
#include <map>

struct go_cqHttp_EndPoint {
    static std::string dump(const std::string& end_point) { return HTTP_HOST + end_point; }
    static constexpr char HTTP_HOST[] = "http://localhost:5700";
    static constexpr char GET_LOGIN_INFO[] = "/get_login_info";
    static constexpr char GET_MSG[] = "/get_msg";
    static constexpr char SEND_PRIVATE_MSG[] = "/send_private_msg";
    static constexpr char SEND_GROUP_MSG[] = "/send_group_msg";
};

class MessageEvent {

};

class MessageBlock {
public:
    using Data = nlohmann::json;
    enum class MessageBlockType {
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
            type_ = MessageBlockType::NOT_SUPPORT;
        }
    }

    [[nodiscard]] const Data& data() const { return data_; }
    [[nodiscard]] MessageBlockType type() const { return type_; }
    [[nodiscard]] const std::string &originType() const { return origin_type_; }
private:
    static const std::map<std::string, MessageBlockType> str_type_hash;

    Data data_;
    MessageBlockType type_;
    std::string origin_type_;
};
const std::map<std::string, MessageBlock::MessageBlockType> MessageBlock::str_type_hash = {
        {"at", MessageBlock::MessageBlockType::AT}, {"text", MessageBlock::MessageBlockType::TEXT},
        {"reply", MessageBlock::MessageBlockType::REPLY}
};
void to_json(nlohmann::json& res, const MessageBlock& mb)
{
    res["data"] = mb.data();
    res["type"] = mb.originType();
}

// FIXME: Qid and time have the same type
using MessageId = int32_t;
using Qid = int64_t;
using MessageChain = std::vector<MessageBlock>;
using Qinfo = nlohmann::json;
using FontType = int32_t;

static constexpr char BOT_NAME[] = "Kinoko";

std::map<Qid, std::unique_ptr<Roleplay>> g_id_chat;

void messageSentHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("messageSentHandler - " + event.dump());
}
void messageHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("messageHandler - " + event.dump());
    static constexpr char para_list[][16] {
        "message_type", "sub_type", "message_id", "user_id", "message", "raw_message", "font", "sender"
    };
    for(const auto * i : para_list) {
        if(!event.contains(i)) {
            WARN_LOG("messageHandler - invalid event without " + std::string(i));
            return;
        }
    }
    enum class MessageEventType {
        PRIVATE_MESSAGE, GROUP_MESSAGE, NOT_SUPPORT
    };

    MessageEventType message_event_type;
    MessageEventType sub_type;

    MessageId message_id;
    Qid sender_id;              // "user_id"

    MessageChain message_chain; // "message"
    std::string raw_message;

    FontType font;
    Qinfo sender_info;          // "sender"

    bool at_me;
    // bool reply_me;   // it's so hard

    // init var
    auto j = event["message_type"];
    if(j.is_string()) {
        if(j == "private") message_event_type = MessageEventType::PRIVATE_MESSAGE;
        else if(j == "group") message_event_type = MessageEventType::GROUP_MESSAGE;
        else {
            WARN_LOG("messageHandler - invalid message type " + j.get<std::string>());
            return;
        }
    }
    j = event["sub_type"];
    if(j.is_string()) {
        if(j == "private") sub_type = MessageEventType::PRIVATE_MESSAGE;
        else if(j == "group") sub_type = MessageEventType::GROUP_MESSAGE;
        else sub_type = MessageEventType::NOT_SUPPORT;
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
        message_chain.emplace_back(i);
    }
    raw_message = event["raw_message"];
    font = event["font"];
    sender_info = event["sender"];
    // at_me
    at_me = false;
    for(const auto &i : message_chain) {
        if(i.type() == MessageBlock::MessageBlockType::AT) {
            Qid at_qq = std::stoll(i.data().at("qq").get<std::string>());
            if(at_qq == self_id)
                at_me = true;
        }
    }

    auto onMessageEvent = [=](){
        auto onGroupMessage = [=](){
            if(!at_me) return ;
            nlohmann::json req_para;
            Qid group_id = event["group_id"].get<Qid>();
            req_para["group_id"] = group_id;
            auto reply_to_sender = [req_para](const std::string &rep) {
                auto j(req_para);
                j["message"] = rep;
                auto r = cpr::Post(cpr::Url(go_cqHttp_EndPoint::HTTP_HOST + std::string(go_cqHttp_EndPoint::SEND_GROUP_MSG)),
                                   cpr::Header{{"Content-Type", "application/json"}},
                                   cpr::Body(j.dump()));
                DEBUG_LOG(r.text);
            };
            std::string msg;
            for(const auto &i : message_chain) {
                if(i.type() == MessageBlock::MessageBlockType::TEXT) {
                    auto temp = i.data()["text"].get<std::string>();
                    StringExtra::trim(temp);
                    msg.append(temp);
                }
            }

            if(!g_id_chat.count(sender_id))
                reply_to_sender(BOT_NAME + std::string("，绝赞休眠中"));
            if(!g_id_chat.count(sender_id)) {
                g_id_chat.emplace(sender_id,std::make_unique<Roleplay>(BOT_NAME, "Human"));
            }
            // auto &chat = g_id_chat[sender_id];
            // if(!chat->speak(msg, reply_to_sender)) {
            //     reply_to_sender(chat->botName() + "还在思考，请稍等一下。");
            // }
        };
        auto onPrivateMessage = [=](){
            nlohmann::json req_para;
            // repeat bot
            req_para["message"] = message_chain;
            req_para["user_id"] = sender_id;
            auto r = cpr::Post(cpr::Url(go_cqHttp_EndPoint::dump(go_cqHttp_EndPoint::SEND_PRIVATE_MSG)),
                               cpr::Header{{"Content-Type", "application/json"}},
                               cpr::Body(req_para.dump()));
            DEBUG_LOG(r.text);
        };

        switch(message_event_type) {
            case MessageEventType::GROUP_MESSAGE:
                DEBUG_LOG("group message");
                onGroupMessage();
                break;
            case MessageEventType::PRIVATE_MESSAGE:
                DEBUG_LOG("private message");
                onPrivateMessage();
                break;
            default:
                WARN_LOG("not support message event type");
                break;
        }
    };
    onMessageEvent();
}
void requestHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("requestHandler - " + event.dump());
}
void noticeHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("noticeHandler - " + event.dump());
}
void metaEventHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("metaEventHandler - " + event.dump());
}
void unknownHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("unknownHandler - " + event.dump());
}

void onPost(const std::string &msg)
{
    auto event = nlohmann::json::parse(msg);
    if(!event.contains("post_type") || !event.contains("self_id") || !event.contains("time")) {
        WARN_LOG("invalid go-cqhttp post");
        return;
    }
    std::string post_type = event["post_type"];
    int64_t time = event["time"];
    Qid self_id = event["self_id"];
    // TODO: pack time
    typedef std::function<void(const nlohmann::json&, Qid, int64_t)> PostHandler;
    const std::map <std::string, PostHandler> handler_map = {
            {"message", messageHandler},
            {"message_sent", messageSentHandler},
            {"request", requestHandler},
            {"notice", noticeHandler},
            {"meta_event", metaEventHandler}
    };
    event.erase("post_type");
    event.erase("time");
    event.erase("self_id");
    auto p = handler_map.find(post_type);
    if(p != handler_map.end()) {
        p->second(event, self_id, time);
    } else {
        unknownHandler(event, self_id, time);
    }
}

int main()
{
    muduo::Logger::setLogLevel(muduo::Logger::INFO);
    muduo::net::EventLoop loop;
    WebsocketServer server(&loop, muduo::net::InetAddress(2050));
    server.setMessageCallback([](const auto &conn, const auto &msg, auto time)
                              { onPost(msg); });

    server.start();
    loop.loop();

    // FIXME: detach thread
    // {
    //     Roleplay r;
    //     r.speak("hello", [](const auto &msg){
    //         printf("%s\n", msg.c_str());
    //     });
    // }
    // int i;
    // scanf("%d", &i);

    return 0;
}