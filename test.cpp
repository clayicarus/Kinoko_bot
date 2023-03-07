//
// Created by clay on 3/2/23.
//

#include "initKey.h"
#include "cstdio"
#include "ChatBot/ChatBot.h"
#include "Logger.h"
#include <memory>

void f_getline(std::string &des, FILE *stream)
{
    char *p = nullptr;
    size_t str_sz;
    auto ret = getline(&p, &str_sz, stream);
    std::unique_ptr<char, void(*)(void*)> u(p, free);
    assert(str_sz > 1 && ret > 0);
    des.assign(u.get(), u.get() + ret - 1);
}

void fmt_scanf()
{
    const int max_len = 5;
    char temp[max_len];
    char fmt[10];
    sprintf(fmt, "%%%ds", max_len - 1);
    scanf(fmt, temp);   // fmt == "%4s"
    printf("%s", temp);
}

int main()
{
    LOG_INFO("bot start");
    ChatBot bot;
    bot.name() = "东海帝皇";
    bot.scene() = "以下是马卡龙和东海帝皇的对话。东海帝皇是一位赛马娘，曾经在日本有马、皋月赏、日本德比等重量级赛事夺得桂冠。"
                  "她性格好强、元气满满、粘人、比较自恋、性格敏感。马卡龙是她的教练，也是东海帝皇的好朋友。"
                  "目白麦昆是东海帝皇的对手兼好友，两人共同竞争，共同进步。\n";
    std::vector<std::pair<std::string, std::string>> v {
            { "马卡龙", {} }, { "目白麦昆", {} }
    };
    for(int i = 0; i < v.size(); i = (i + 1) % v.size()) {
        auto &[speaker, content] = v[i];
        printf("%s: ", speaker.c_str());
        f_getline(content, stdin);
        if(content.empty())
            continue;
        bot.speak(speaker, content);
        printf("%s: %s\n", bot.name().c_str(), bot.getOneReply(speaker).c_str());
    }

    return 0;
}