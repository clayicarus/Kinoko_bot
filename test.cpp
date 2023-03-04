//
// Created by clay on 3/2/23.
//

#include "dependency.h"
#include "cstdio"
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

    TestChat chat;
    std::string s;
    printf("%s:%d\n", __FILE__, __LINE__);
    for(int i = 0; i < 10; ++i) {
        f_getline(s, stdin);
        printf("%s\n[Cache]: ", chat.say(s).c_str());
        chat.printCache();
    }
    // fmt_scanf();
    // char temp[5];
    // scanf("%s", temp);
    // printf("%s", temp);

    return 0;
}