#include "models/UserModel.hpp"
#include <pqxx/pqxx>

bool UserModel::create(const std::string& username,const std::string& password_hash, const std::string& role) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("INSERT INTO utilisateurs (username, password_hash, role) VALUES (" + W.quote(username) + "," + W.quote(password_hash) + "," + W.quote(role)+ ")").no_rows();
        W.commit();
        return true;

    }catch (const std::exception& e) {
        return false;
    }
}

bool UserModel::authenticate(const std::string& username, const std::string& password) {
    try {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::nontransaction N(c);
        pqxx::result r = N.exec("SELECT password_hash FROM utilisateurs WHERE username = " + N.quote(username));

        if(r.empty()) {
            return false;
        }

        return r[0][0].as<std::string>() == password;

    }catch (const std::exception& e) {
        return false;
    }
}