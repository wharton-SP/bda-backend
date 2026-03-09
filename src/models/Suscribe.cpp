#include "models/SuscribeModel.hpp"
#include <pqxx/pqxx>
#include <vector>
#include <string>

bool SuscribeModel::create(const int matricule, const std::string& nom, const int droit_inscription, const std::string& utilisateur) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("SET myapp.current_user_name = "+ W.quote(utilisateur));
        W.exec("INSERT INTO inscription (matricule, nom, droit_inscription) VALUES (" + W.quote(matricule) + "," + W.quote(nom) + "," + W.quote(droit_inscription) + ")");
        W.commit();
        return true;

    }catch (const std::exception& e) {
        return false;
    }
}

bool SuscribeModel::update(const int matricule, const std::string& nom, const int droit_inscription, const std::string& utilisateur) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("SET myapp.current_user_name = "+ W.quote(utilisateur));
        W.exec("UPDATE inscription SET nom = " + W.quote(nom) + ", droit_inscription = " + W.quote(droit_inscription) + " WHERE matricule = " + W.quote(matricule));
        W.commit();
        return true;

    }catch (const std::exception& e) {
        return false;
    }
}

bool SuscribeModel::remove(const int matricule, const std::string& utilisateur) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("SET myapp.current_user_name = "+ W.quote(utilisateur));
        W.exec("DELETE FROM inscription WHERE matricule = " + W.quote(matricule));
        W.commit();
        return true;
    }catch (const std::exception& e) {
        return false;
    }
}

std::vector<Suscribe> SuscribeModel::getAll() {
    std::vector<Suscribe> list;
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::nontransaction N(c);

        pqxx::result r = N.exec("SELECT matricule, nom, droit_inscription FROM inscription");

        for (auto const &row : r) {
            Suscribe s;
            s.matricule = row[0].as<int>();
            s.nom = row[1].as<std::string>();
            s.droit_inscription = row[2].as<double>();
            list.push_back(s);
        }

    }catch (const std::exception& e) {
            throw std::runtime_error("Failed to fetch subscriptions: " + std::string(e.what()));
    }
    return list;
}
