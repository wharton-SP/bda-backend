#include "controllers/AuditController.hpp"
#include "models/AuditModel.hpp"
#include "crow.h"
#include <iostream>

namespace AuditController {

void handle_get_logs(const crow::request& req, crow::response& res) {
    try {

        auto logs = AuditModel::getAllLogs();

        crow::json::wvalue json_response;

        json_response["status"] = "success";
        json_response["count"] = logs.size();

        auto& json_logs = json_response["logs"];

        for (size_t i = 0; i < logs.size(); ++i) {
            json_logs[i]["id"] = logs[i].id;
            json_logs[i]["type_action"] = logs[i].type_action;
            json_logs[i]["date_mise_a_jour"] = logs[i].date_mise_a_jour;
            json_logs[i]["matricule"] = logs[i].matricule;
            json_logs[i]["nom"] = logs[i].nom;
            json_logs[i]["droit_ancien"] = logs[i].droit_ancien;
            json_logs[i]["droit_nouv"] = logs[i].droit_nouv;
            json_logs[i]["utilisateur"] = logs[i].utilisateur;
        }

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(json_response.dump());

    } catch (const std::exception& e) {
        crow::json::wvalue error_response;
        error_response["status"] = "error";
        error_response["message"] = e.what();

        res.code = 500;
        res.set_header("Content-Type", "application/json");
        res.write(error_response.dump());

        std::cerr << "Error in handle_get_logs: " << e.what() << std::endl;
    }

    res.end();
}

void handle_get_stat(const crow::request& req, crow::response& res){
    try {
        AuditStats stats = AuditModel::getStat();

        crow::json::wvalue json_response;
        json_response["status"] = "success";

        json_response["data"]["insertions"] = stats.insertions;
        json_response["data"]["modifications"] = stats.modifications;
        json_response["data"]["deletions"] = stats.deletions;
        json_response["data"]["total_audits"] = stats.total_audits;
        json_response["data"]["distinct_users"] = stats.distinct_users;
        json_response["data"]["concerned_students"] = stats.concerned_students;
        json_response["data"]["first_action"] = stats.first_action;
        json_response["data"]["last_action"] = stats.last_action;

        auto& top_users_json = json_response["data"]["top_users"];
        for (size_t i = 0; i < stats.top_users.size(); ++i) {
            top_users_json[i]["username"] = stats.top_users[i].username;
            top_users_json[i]["action_count"] = stats.top_users[i].action_count;
        }

        auto& actions_per_day_json = json_response["data"]["actions_per_day"];
        int index = 0;
        for (const auto& [day, count] : stats.actions_per_day) {
            actions_per_day_json[index]["day"] = day;
            actions_per_day_json[index]["count"] = count;
            index++;
        }

        res.code = 200;
        res.set_header("Content-Type", "application/json");
        res.write(json_response.dump());

    } catch (const std::exception& e) {
        crow::json::wvalue error_response;
        error_response["status"] = "error";
        error_response["message"] = e.what();

        res.code = 500;
        res.set_header("Content-Type", "application/json");
        res.write(error_response.dump());

        std::cerr << "Error in handle_get_stat: " << e.what() << std::endl;
    }

    res.end();
}

}
