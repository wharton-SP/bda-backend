#ifndef SUSCRIBE_CONTROLLER_HPP
#define SUSCRIBE_CONTROLLER_HPP
#include <crow.h>

namespace SuscribeController {
    void handle_get_all(const crow::request& req, crow::response& res);
    void handle_create(const crow::request& req, crow::response& res);
    void handle_update(const crow::request& req, crow::response& res);
    void handle_delete(const crow::request& req, crow::response& res);
}

#endif
