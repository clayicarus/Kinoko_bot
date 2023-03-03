//
// Created by clay on 3/2/23.
//

#ifndef ATRI_OPENAIAPI_H
#define ATRI_OPENAIAPI_H

#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

class OpenAI_API {
public:
    OpenAI_API() = delete;

    typedef nlohmann::json API_Response;
    static const std::string API_KEY;   // init required

    static API_Response listModels();

    typedef std::string pathParameter;
    static API_Response retrieveModel(const pathParameter &model_name);

    typedef nlohmann::json CreateCompletionPayload;
    static API_Response createCompletion(const CreateCompletionPayload &payload);
private:
    struct API_List;
    static API_Response dumpResponse(const cpr::Response &r);
    static bool isEmptyInPayload(const nlohmann::json &payload, std::initializer_list<std::string> &&args);
};
struct OpenAI_API::API_List {
    static constexpr char LIST_MODELS[] = "https://api.openai.com/v1/models/";
    static constexpr char CREATE_COMPLETION[] = "https://api.openai.com/v1/completions";
};

#endif //ATRI_OPENAIAPI_H
