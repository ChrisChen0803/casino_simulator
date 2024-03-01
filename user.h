#include <string>
#ifndef USER_H  // Header guards to prevent multiple inclusion
#define USER_H

class User {
private:
    // Member variables
    std::string name;
    std::string password;
    int balance;

public:
    // Constructor
    User(const std::string& name,const std::string& password,int balance);
    User();
    

    // Member functions
    void setName(const std::string& newName);
    void display() const;
    void setBalance(int newBalance);
    void setPassword(const std::string& newPassword);
    std::string getName();
    std::string getPassword();
    int getBalance();
};

#endif