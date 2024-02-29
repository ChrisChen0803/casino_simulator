#include "login.h"
#include <iostream>
#include <string>
Login::Login() {
    loadCredentialsFromFile("credentials.txt");
}
bool Login::authenticate(const std::string& username, const std::string& password){
    auto pair = credentials.find(username);
    //std::cout<<1<<std::endl;
    if(pair != credentials.end() && pair->second.getPassword()==password) {
        return true;
    }
    return false;
}
void Login::loadCredentialsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string username, password, balance;
        while (file >> username >> password >> balance) {
            User user(username, password, std::stoi(balance));
            credentials[username] = user;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
User Login::getUser(std::string username){
    auto it = credentials.find(username);
    if(it==credentials.end()){
        return User();
    }
    else{
        User u = it->second;
        return u;
    }
}
void Login::updateCred(std::string username, User user){
    credentials[username] = user;
}
void Login::saveCredentialsToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::trunc); // Append mode
    if (file.is_open()) {
        for (const auto& pair : credentials) {
            //std::cout<<pair.first<<std::endl;
            User user = pair.second;
            std::string username = user.getName();
            std::string password = user.getPassword();
            std::string balance = std::to_string(user.getBalance());
            file << username << " " << password << " " << balance << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}
bool Login::registerUser(const std::string& username, const std::string& password) {
    if (credentials.find(username) == credentials.end()) {
        User user(username, password, 0);
        credentials[username] = user;
        return true;
    }
    return false;
}