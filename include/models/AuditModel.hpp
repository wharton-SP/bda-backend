#ifndef AUDIT_MODEL_HPP
#define AUDIT_MODEL_HPP

#include <string>
#include <vector>
#include <map>

struct AuditLog {
    int id;
    std::string type_action;
    std::string date_mise_a_jour;
    int matricule;
    std::string nom;
    double droit_ancien;
    double droit_nouv;
    std::string utilisateur;
};

struct AuditStats {
    int insertions = 0;
    int modifications = 0;
    int deletions = 0;

    int total_audits = 0;
    int distinct_users = 0;
    int concerned_students = 0;
    std::string first_action;
    std::string last_action;

    struct UserStat {
        std::string username;
        int action_count;
    };
    std::vector<UserStat> top_users;

    std::map<std::string, int> actions_per_day;
};

class AuditModel {
public:
    static std::vector<AuditLog> getAllLogs();
    static AuditStats getStat();
};

#endif
