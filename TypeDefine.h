//
// Created by clay on 3/30/23.
//

#ifndef KINOKO_TYPEDEFINE_H
#define KINOKO_TYPEDEFINE_H

// FIXME: Qid and time have the same type
#include <nlohmann/json.hpp>
#include <cstdint>

using MessageId = int32_t;
using Qid = int64_t;
using Qinfo = nlohmann::json;
using FontType = int32_t;

#endif //KINOKO_TYPEDEFINE_H
