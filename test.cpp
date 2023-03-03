//
// Created by clay on 3/2/23.
//

#include "dependency.h"
#include "cstdio"
#include <memory>

void f_getline(std::string &des, FILE *stream)
{
    char *p;
    std::unique_ptr<char, void(*)(void*)> u(p, free);
    size_t sz;
    getline(&p, &sz, stream);
    des.assign(p, p + sz);
}

int main()
{
    TestChat chat;
    std::string s;
    for(int i = 0; i < 10; ++i) {
        // const int max_len = 80;
        // char temp[max_len];
        // char fmt[10];
        // sprintf(fmt, "%%%ds", max_len - 1);
        // scanf(fmt, temp);
        f_getline(s, stdin);
        printf("%s", s.c_str());
        // printf("%s\n[Cache]: ", chat.say(s).c_str());
        // chat.printCache();
    }

    return 0;
}