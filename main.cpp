//
// Created by clay on 3/2/23.
//

#include <iostream>
#include "Chat/Chat.h"
#include "OpenAI_API/OpenAI_API.h"

void f_getline(std::string &des, FILE *stream)
{
    char *p = nullptr;
    size_t str_sz;
    auto ret = getline(&p, &str_sz, stream);
    std::unique_ptr<char, void(*)(void*)> u(p, free);
    assert(str_sz > 1 && ret > 0);
    des.assign(u.get(), u.get() + ret - 1);
}

int main()
{
    std::cout << OpenAI_API::retrieveModel("gpt-3.5-turbo") << std::endl;
    std::cout << OpenAI_API::retrieveModel("gpt-3.5-turbo-0301") << std::endl;
    std::cout << OpenAI_API::retrieveModel("text-davinci-003") << std::endl;
    Chat bot;
    const std::string speaker = "Human";
    while(true) {
        std::string content;
        printf("%s: ", speaker.c_str());
        f_getline(content, stdin);
        if(content.empty()) break;
        bot.speak("Human", content);
        auto rep = bot.getOneReply(speaker);
        printf("%s: %s\n", bot.name().c_str(), rep.c_str());
    }

    return 0;
}