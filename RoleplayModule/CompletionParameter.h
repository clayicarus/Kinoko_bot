//
// Created by clay on 3/3/23.
//

#ifndef ATRI_COMPLETIONPARAMETER_H
#define ATRI_COMPLETIONPARAMETER_H

#include <nlohmann/json.hpp>
#include <string>

class CompletionParameter {
    friend class ChatBot;
public:
    CompletionParameter() :
        model_("text-davinci-003"),
        max_tokens_(200),
        temperature_(.3f),
        frequency_penalty_(.5f),
        presence_penalty_(.5f)
    {}
    [[nodiscard]] const nlohmann::json &getPara();
    unsigned &max_tokens() { return max_tokens_; }
    float &temperature() { return temperature_; }
    float &frequency_penalty() { return frequency_penalty_; }
    float &presence_penalty() { return presence_penalty_; }
    std::string &model() { return model_; }

    void setPrompt(const std::string &prompt) { para_["prompt"] = prompt; }
    void setStop(const std::vector<std::string> &stop) { para_["stop"] = stop; }
private:
    std::string model_;
    unsigned max_tokens_;
    float temperature_;
    float frequency_penalty_;
    float presence_penalty_;
    nlohmann::json para_;

};


#endif //ATRI_COMPLETIONPARAMETER_H
