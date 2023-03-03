//
// Created by clay on 3/3/23.
//

#ifndef ATRI_TESTCHAT_H
#define ATRI_TESTCHAT_H
#include <string>
#include <nlohmann/json.hpp>
#include "OpenAI_API/OpenAI_API.h"

class TestChat {
public:
    TestChat()
        : init("The following is a conversation with an AI assistant. "
               "The assistant is helpful, creative, clever, and very friendly. "
               "\n\nHuman: Hello, who are you?\nAI: I am Atri, an AI realized with GPT. How can Atri help you today?\n"
               "Human: 你可以说中文吗？\nAI: 当然可以，Atri有什么可以帮助您？\n"),
          head("Human: ")
    {
        parameter = R"(
            {
                "model": "text-davinci-003",
                "max_tokens": 200,
                "temperature": 0.3,
                "top_p": 1,
                "frequency_penalty": 0.5,
                "presence_penalty": 0.5,
                "stop": ["\nHuman: ", "\nAI: "]
            }
          )"_json;
    }
    std::string say(const std::string &s)
    {
        std::string res;
        auto sentence = head + s + "\n";
        parameter["prompt"] = init + cache + sentence;
        auto r = OpenAI_API::createCompletion(parameter);
        if(r["status_code"] == 200) {
            std::string response = r["response_data"]["choices"][0]["text"];
            res = response;
            cache += sentence + response + "\n";
        } else {
            std::string err_msg = r["error_message"];
            res = "[Network Error]: " + err_msg;
        }
        return res;
    }
    void clearCache() { cache.clear(); }
    void printCache() const { printf("%s", cache.c_str()); }
private:
    std::string init;
    std::string cache;
    std::string head;
    nlohmann::json parameter;
};


#endif //ATRI_TESTCHAT_H
