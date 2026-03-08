#ifndef SUSCRIBE_MODEL_HPP
#define SUSCRIBE_MODEL_HPP

#include <string>

struct Suscribe {
    int matricule;
    std::string nom;
    int droit_inscription;
};

class SuscribeModel {
    public:
        static bool create(const int matricule, const std::string& nom, const int droit_inscription);
        static bool update(const int matricule, const std::string& nom, const int droit_inscription);
        static bool remove(const int matricule);
};

#endif