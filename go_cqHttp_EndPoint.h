//
// Created by clay on 3/30/23.
//

#ifndef KINOKO_GO_CQHTTP_ENDPOINT_H
#define KINOKO_GO_CQHTTP_ENDPOINT_H

#include <string>

struct go_cqHttp_EndPoint {
    static std::string dump(const std::string& end_point) { return HTTP_HOST + end_point; }
    static constexpr char HTTP_HOST[] = "http://localhost:5700";
    static constexpr char GET_LOGIN_INFO[] = "/get_login_info";
    static constexpr char GET_MSG[] = "/get_msg";
    static constexpr char SEND_PRIVATE_MSG[] = "/send_private_msg";
    static constexpr char SEND_GROUP_MSG[] = "/send_group_msg";
};


#endif //KINOKO_GO_CQHTTP_ENDPOINT_H
