#ifndef SUSCRIBE_MODEL_HPP
#define SUSCRIBE_MODEL_HPP

#include <string>
#include <vector>

struct Suscribe {
    int matricule;
    std::string nom;
    int droit_inscription;
};

class SuscribeModel {
    public:
        static std::vector<Suscribe> getAll();
        static bool create(const int matricule, const std::string& nom, const int droit_inscription, const std::string& utilisateur);
        static bool update(const int matricule, const std::string& nom, const int droit_inscription, const std::string& utilisateur);
        static bool remove(const int matricule, const std::string& utilisateur);
};

#endif
