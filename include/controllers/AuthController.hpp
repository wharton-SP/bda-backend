#ifndef AUTH_CONTROLLER_HPP
#define AUTH_CONTROLLER_HPP
#include <crow.h>

namespace AuthController {
    void handle_signin(const crow::request& req, crow::response& res);
    void handle_login(const crow::request& req, crow::response& res);
}

#endif