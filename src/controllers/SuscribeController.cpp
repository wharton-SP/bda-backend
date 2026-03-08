#include "controllers/SuscribeController.hpp"
#include "crow.h"
#include "models/SuscribeModel.hpp"

namespace SuscribeController {
    void handle_create(const crow::request& req, crow::response& res) {
        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.write("Invalid JSON");
            res.end();
            return;
        }

        if (SuscribeModel::create(body["matricule"].i(), body["nom"].s(), body["droit_inscription"].i())) {
            res.code = 201;
            res.write("Suscribe Created !");
        }
        else {
            res.code = 400;
            res.write("Error creating suscribe !");
        }
        res.end();
    } 

    void handle_update(const crow::request& req, crow::response& res){
        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.write("Invalid JSON");
            res.end();
            return;
        }

        if (SuscribeModel::update(body["matricule"].i(), body["nom"].s(), body["droit_inscription"].i())) {
            res.code = 200;
            res.write("Suscribe updated !");
        }
        else {
            res.code = 400;
            res.write("Error updating suscribe !");
        }
        res.end();
    }

    void handle_delete(const crow::request& req, crow::response& res){
        auto body = crow::json::load(req.body);
        if (!body) {
            res.code = 400;
            res.write("Invalid JSON");
            res.end();
            return;
        }

        if (SuscribeModel::remove(body["matricule"].i())) {
            res.code = 200;
            res.write("Suscribe deleted !");
        }
        else {
            res.code = 400;
            res.write("Error deleting suscribe !");
        }
        res.end();
    }
}