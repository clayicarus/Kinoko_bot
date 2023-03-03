//
// Created by clay on 3/2/23.
//

#include "dependency.h"
#include "cstdio"
#include <vector>

int main()
{
    TestChat chat;
    std::string s;
    for(int i = 0; i < 10; ++i) {
        const int max_len = 80;
        char temp[max_len];
        char fmt[10];
        sprintf(fmt, "%%%ds", max_len - 1);
        scanf(fmt, temp);
        s = temp;
        printf("%s\n[Cache]: ", chat.say(s).c_str());
        chat.printCache();
    }

    return 0;
}