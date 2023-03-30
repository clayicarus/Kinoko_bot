//
// Created by clay on 3/2/23.
//

#include "RoleplayModule/Roleplay.h"
#include "OpenAI_API/OpenAI_API.h"
#include "WebsocketServer/WebsocketServer.h"
#include "muduo/net/EventLoop.h"
#include "Logger.h"
#include "base/StringExtra.h"
#include "MessageEvent.h"
#include "go_cqHttp_EndPoint.h"

#include <nlohmann/json.hpp>
#include <map>

#include "BotConstant.h"

using MessageEventCallback = std::function<void(const MessageEvent&, Qid, int64_t)>;
MessageEventCallback onMessage;

static constexpr char BOT_NAME[] = "Kinoko";
std::map<Qid, std::unique_ptr<Roleplay>> g_id_chat;

void messageSentHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("messageSentHandler - " + event.dump());
}
void messageHandler(const nlohmann::json& event, Qid self_id, int64_t time)
{
    DEBUG_LOG("messageHandler - " + event.dump());
    for(const auto * i : message_event_paralist) {
        if(!event.contains(i)) {
            WARN_LOG("messageHandler - invalid event without " + std::string(i));
            return;
        }
    }
    onMessage(MessageEvent(event), self_id, time);
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

void to_json(nlohmann::json& res, const MessageBlock& mb)
{
    res["data"] = mb.data();
    res["type"] = mb.originType();
}

int main()
{
    onMessage = [&](const auto &event, Qid self_id, auto time) {
        DEBUG_LOG("on message - " + event.rawEvent().dump());
        auto onGroupMessage = [&](){
            if(!event.messageChain().isAt(self_id)) return ;
            nlohmann::json req_para;
            auto group_id = event.rawEvent().at("group_id").template get<Qid>();
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
            for(const auto &i : event.messageChain().array()) {
                if(i.type() == MessageBlock::Type::TEXT) {
                    auto temp = i.data()["text"].template get<std::string>();
                    StringExtra::trim(temp);
                    msg.append(temp);
                }
            }

            reply_to_sender(BOT_NAME + std::string("，绝赞休眠中"));
            if(!g_id_chat.count(self_id)) {
                g_id_chat.emplace(self_id,std::make_unique<Roleplay>(BOT_NAME, "Human"));
            }
            // auto &chat = g_id_chat[sender_id];
            // if(!chat->speak(msg, reply_to_sender)) {
            //     reply_to_sender(chat->botName() + "还在思考，请稍等一下。");
            // }
        };
        auto onPrivateMessage = [&](){
            nlohmann::json req_para;
            // repeat bot
            req_para["message"] = event.messageChain().array();
            req_para["user_id"] = event.senderId();
            auto r = cpr::Post(cpr::Url(go_cqHttp_EndPoint::dump(go_cqHttp_EndPoint::SEND_PRIVATE_MSG)),
                               cpr::Header{{"Content-Type", "application/json"}},
                               cpr::Body(req_para.dump()));
            DEBUG_LOG(r.text);
        };

        switch(event.eventType()) {
            case MessageEvent::Type::GROUP_MESSAGE:
                DEBUG_LOG("group message");
                onGroupMessage();
                break;
            case MessageEvent::Type::PRIVATE_MESSAGE:
                DEBUG_LOG("private message");
                onPrivateMessage();
                break;
            default:
                WARN_LOG("not support message event type");
                break;
        }
    };

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