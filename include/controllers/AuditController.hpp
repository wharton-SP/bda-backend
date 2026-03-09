#ifndef AUDIT_CONTROLLER_HPP
#define AUDIT_CONTROLLER_HPP
#include "crow.h"

namespace AuditController {
    void handle_get_logs(const crow::request& req, crow::response& res);
    void handle_get_stat(const crow::request& req, crow::response& res);
}

#endif
