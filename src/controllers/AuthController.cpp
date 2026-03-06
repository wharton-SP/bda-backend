#include "controllers/AuthController.hpp"
#include "crow.h"
#include "models/UserModel.hpp"

namespace AuthController {
    void handle_signin(const crow::request& req, crow::response& res) {
        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.write("Invalid JSON");
            res.end();
            return;
        }

        if (UserModel::create(body["username"].s(), body["password"].s(), body["role"].s())) {
            res.code = 201;
            res.write("User Created !");
        }
        else {
            res.code = 400;
            res.write("Error creating user !");
        }
        res.end();
    } 

    void handle_login(const crow::request& req, crow::response& res){
        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.write("Invalid JSON");
            res.end();
            return;
        }

        if (UserModel::authenticate(body["username"].s(), body["password"].s())) {
            res.code = 200;
            res.write("Login successful !");
        }
        else {
            res.code = 401;
            res.write("Invalid credentials !");
        }
        res.end();
    }
}