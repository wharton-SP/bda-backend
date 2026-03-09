#include "models/AuditModel.hpp"
#include <pqxx/pqxx>
#include <iostream>

std::vector<AuditLog> AuditModel::getAllLogs() {
    std::vector<AuditLog> logs;

    const std::string conn_str = "host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda";

    try {
        pqxx::connection c(conn_str);

        if (!c.is_open()) {
            throw std::runtime_error("Impossible de se connecter à la base de données");
        }

        pqxx::nontransaction N(c);

        pqxx::result r = N.exec(
            "SELECT id, type_action, date_mise_a_jour, matricule, nom, "
            "droit_ancien, droit_nouv, utilisateur "
            "FROM audit_inscription "
            "ORDER BY date_mise_a_jour DESC"
            );

        logs.reserve(r.size());

        for (auto const &row : r) {
            AuditLog log;

            log.id = row[0].as<int>();
            log.type_action = row[1].as<std::string>();
            log.date_mise_a_jour = row[2].as<std::string>();

            log.matricule = row[3].is_null() ? 0 : row[3].as<int>();
            log.nom = row[4].is_null() ? "" : row[4].as<std::string>();

            log.droit_ancien = row[5].is_null() ? 0.0 : row[5].as<double>();
            log.droit_nouv = row[6].is_null() ? 0.0 : row[6].as<double>();

            log.utilisateur = row[7].as<std::string>();

            logs.push_back(log);
        }

    } catch (const pqxx::sql_error &e) {

        std::cerr << "Error SQL : " << e.what() << std::endl;
        std::cerr << "Request : " << e.query() << std::endl;
        throw;

    } catch (const std::exception &e) {
        std::cerr << "Error : " << e.what() << std::endl;
        throw;
    }

    return logs;
}

AuditStats AuditModel::getStat() {
    AuditStats stats{};

    const std::string conn_str = "host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda";

    try {
        pqxx::connection c(conn_str);

        if (!c.is_open()) {
            throw std::runtime_error("Unable to connect to database");
        }

        pqxx::nontransaction N(c);

        pqxx::result r1 = N.exec(
            "SELECT "
            "COUNT(*) as total_audits, "
            "COUNT(DISTINCT utilisateur) as distinct_users, "
            "COUNT(DISTINCT matricule) as concerned_students, "
            "MIN(date_mise_a_jour) as first_action, "
            "MAX(date_mise_a_jour) as last_action "
            "FROM audit_inscription"
            );

        if (!r1.empty()) {
            const auto& row = r1[0];
            stats.total_audits = row["total_audits"].as<int>();
            stats.distinct_users = row["distinct_users"].as<int>();
            stats.concerned_students = row["concerned_students"].as<int>();
            stats.first_action = row["first_action"].as<std::string>();
            stats.last_action = row["last_action"].as<std::string>();
        }

        pqxx::result r2 = N.exec(
            "SELECT "
            "COALESCE(SUM(CASE WHEN type_action = 'INSERT' THEN 1 ELSE 0 END), 0) as insertions, "
            "COALESCE(SUM(CASE WHEN type_action = 'UPDATE' THEN 1 ELSE 0 END), 0) as modifications, "
            "COALESCE(SUM(CASE WHEN type_action = 'DELETE' THEN 1 ELSE 0 END), 0) as deletions "
            "FROM audit_inscription"
            );

        if (!r2.empty()) {
            const auto& row = r2[0];
            stats.insertions = row["insertions"].as<int>();
            stats.modifications = row["modifications"].as<int>();
            stats.deletions = row["deletions"].as<int>();
        }

        pqxx::result r3 = N.exec(
            "SELECT utilisateur, COUNT(*) as action_count "
            "FROM audit_inscription "
            "GROUP BY utilisateur "
            "ORDER BY action_count DESC "
            "LIMIT 5"
            );

        for (const auto& row : r3) {
            stats.top_users.push_back({
                row["utilisateur"].as<std::string>(),
                row["action_count"].as<int>()
            });
        }

        pqxx::result r4 = N.exec(
            "SELECT DATE(date_mise_a_jour) as day, COUNT(*) as action_count "
            "FROM audit_inscription "
            "WHERE date_mise_a_jour >= CURRENT_DATE - INTERVAL '7 days' "
            "GROUP BY DATE(date_mise_a_jour) "
            "ORDER BY day DESC"
            );

        for (const auto& row : r4) {
            stats.actions_per_day[row["day"].as<std::string>()] = row["action_count"].as<int>();
        }

    } catch (const pqxx::sql_error& e) {
        std::cerr << "SQL error in getStats: " << e.what() << std::endl;
        std::cerr << "Query: " << e.query() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error in getStats: " << e.what() << std::endl;
    }

    return stats;
}
