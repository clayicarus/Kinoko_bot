//
// Created by clay on 3/3/23.
//

#include "CompletionParameter.h"

const nlohmann::json &CompletionParameter::getPara()
{
    para_["model"] = model_;
    para_["max_tokens"] = max_tokens_;
    para_["temperature"] = temperature_;
    para_["frequency_penalty"] = frequency_penalty_;
    para_["presence_penalty"] = presence_penalty_;
    return para_;
}
