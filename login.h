#ifndef LOGIN_H
#define LOGIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include "user.cpp"

class Login {
private:
    std::unordered_map<std::string, User> credentials;

public:
    Login(); // Constructor to load credentials from file
    void loadCredentialsFromFile(const std::string& filename);
    void saveCredentialsToFile(const std::string& filename);
    void updateCred(std::string username, User user);
    User getUser(std::string username);
    bool authenticate(const std::string& username, const std::string& password);
    bool registerUser(const std::string& username, const std::string& password);
};

#endif // LOGIN_H