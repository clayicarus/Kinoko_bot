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
    std::string speaker = "John";
    while(true) {
        std::string con;
        f_getline(con, stdin);
        if(con.empty())
            break;
        bot.speak(speaker, con);
        printf("%s\n", bot.getOneReply(speaker).c_str());
    }
    // printf("%s", OpenAI_API::listModels().dump().c_str());

    return 0;
}