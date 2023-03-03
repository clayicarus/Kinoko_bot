//
// Created by clay on 3/2/23.
//

#include "dependency.h"

int main()
{
    // store a string in a JSON value
    nlohmann::json j = R"(
      {
          "model": "text-davinci-003",
          "prompt": "Say this is a test",
          "max_tokens": 7,
          "temperature": 0
      }
    )"_json;
    j = R"(
      {
          "model": "text-davinci-003",
          "prompt": "Say this is a test"
      }
    )"_json;
    std::string prompt;

    auto r = OpenAI_API::createCompletion(j);
    std::cout << r << std::endl;

    return 0;
}