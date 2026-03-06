#include "routes/AuthRoutes.hpp"
#include "controllers/AuthController.hpp"

void setup_auth_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/auth/signin").methods(crow::HTTPMethod::Post)(AuthController::handle_signin);
    CROW_ROUTE(app, "/auth/login").methods(crow::HTTPMethod::Post)(AuthController::handle_login);
}