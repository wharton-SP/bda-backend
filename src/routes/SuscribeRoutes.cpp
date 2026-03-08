#include "routes/SuscribeRoutes.hpp"
#include "controllers/SuscribeController.hpp"

void setup_suscribe_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/suscribe/create").methods(crow::HTTPMethod::Post)(SuscribeController::handle_create);
    CROW_ROUTE(app, "/suscribe/update").methods(crow::HTTPMethod::Put)(SuscribeController::handle_update);
    CROW_ROUTE(app, "/suscribe/delete").methods(crow::HTTPMethod::Delete)(SuscribeController::handle_delete);
}