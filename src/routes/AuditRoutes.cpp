#include "routes/AuditRoutes.hpp"
#include "controllers/AuditController.hpp"

void setup_audit_routes (crow::SimpleApp &app) {
    CROW_ROUTE(app, "/audit/logs").methods(crow::HTTPMethod::GET) (AuditController::handle_get_logs);
    CROW_ROUTE(app, "/audit/stat").methods(crow::HTTPMethod::GET)(AuditController::handle_get_stat);
}
