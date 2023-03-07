//
// Created by clay on 3/2/23.
//

#include "initKey.h"
#include <iostream>

int main()
{
    std::cout << OpenAI_API::retrieveModel("gpt-3.5-turbo") << std::endl;
    std::cout << OpenAI_API::retrieveModel("gpt-3.5-turbo-0301") << std::endl;
    std::cout << OpenAI_API::retrieveModel("text-davinci-003") << std::endl;

    return 0;
}