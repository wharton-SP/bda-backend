#include "models/SuscribeModel.hpp"
#include <pqxx/pqxx>

bool SuscribeModel::create(const int matricule, const std::string& nom, const int droit_inscription) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("INSERT INTO inscription (matricule, nom, droit_inscription) VALUES (" + W.quote(matricule) + "," + W.quote(nom) + "," + W.quote(droit_inscription) + ")").no_rows();
        W.commit();
        return true;

    }catch (const std::exception& e) {
        return false;
    }
}

bool SuscribeModel::update(const int matricule, const std::string& nom, const int droit_inscription) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("UPDATE inscription SET nom = " + W.quote(nom) + ", droit_inscription = " + W.quote(droit_inscription) + " WHERE matricule = " + W.quote(matricule)).no_rows();
        W.commit();
        return true;

    }catch (const std::exception& e) {
        return false;
    }
}

bool SuscribeModel::remove(const int matricule) {
    try  {
        pqxx::connection c("host=localhost port=5432 dbname=gestion_etudiant user=bda password=bdabda");
        pqxx::work W(c);
        W.exec("DELETE FROM inscription WHERE matricule = " + W.quote(matricule)).no_rows();
        W.commit();
        return true;
    }catch (const std::exception& e) {
        return false;
    }
}