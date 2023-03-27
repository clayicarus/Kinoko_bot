//
// Created by clay on 3/2/23.
//

#include "OpenAI_API.h"

using namespace nlohmann;
using namespace cpr;

OpenAI_API::API_Response OpenAI_API::dumpResponse(const cpr::Response &r)
{
    API_Response res;
    if(r.error.code == cpr::ErrorCode::OK) {
        res["is_error"] = false;
        res["status_code"] = r.status_code;
        res["response_data"] = nlohmann::json::parse(r.text);
    } else {
        res["is_error"] = true;
        res["error_message"] = r.error.message;
    }
    return res;
}

OpenAI_API::API_Response OpenAI_API::listModels()
{
    Response r = Get(Url(API_List::LIST_MODELS),
                     Header{{"Authorization", "Bearer " + API_KEY}});
    return dumpResponse(r);
}

OpenAI_API::API_Response OpenAI_API::retrieveModel(const std::string &model_name)
{
    Response r = Get(Url(API_List::RETRIEVE_MODEL + model_name),
                     Header{{"Authorization", "Bearer " + API_KEY}});
    return dumpResponse(r);
}

OpenAI_API::API_Response OpenAI_API::createCompletion(const OpenAI_API::CreateCompletionPayload &payload)
{
    if(isEmptyInPayload(payload, {"model"})) {
        // throw;
    }
    Response r = Post(Url(API_List::CREATE_COMPLETION),
                      Header{{"Authorization", "Bearer " + API_KEY}},
                      Header{{"Content-Type", "application/json"}},
                      Body(payload.dump()));
    return dumpResponse(r);
}

bool OpenAI_API::isEmptyInPayload(const nlohmann::json &payload, std::initializer_list<std::string> &&args)
{
    for(auto &i : args) {
        if(!payload.contains(i))
            return true;
    }
    return false;
}

OpenAI_API::API_Response OpenAI_API::completionTest() {
    nlohmann::json payload(R"(
        {
            "model": "text-davinci-003",
            "prompt": "Say this is a test",
            "max_tokens": 7,
            "temperature": 0
        }
    )"_json);
    Response r = Post(Url(API_List::CREATE_COMPLETION),
                      Header{{"Authorization", "Bearer " + API_KEY}},
                      Header{{"Content-Type", "application/json"}},
                      Body(payload.dump()));
    return dumpResponse(r);
}

