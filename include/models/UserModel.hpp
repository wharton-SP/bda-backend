#ifndef USER_MODEL_HPP
#define USER_MODEL_HPP

#include <string>
#include <optional>

struct User {
    int id;
    std::string username;
    std::string password_hash;
    std::string role;
};

class UserModel {
public:
    static bool create(const std::string& username, const std::string& password_hash, const std::string& role);
    static bool authenticate(const std::string& username, const std::string& password);
};

#endif
