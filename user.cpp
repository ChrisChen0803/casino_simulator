
#ifndef USER_CPP
#define USER_CPP
#include "user.h"
#include <iostream>

// Constructor
User::User(const std::string &name, const std::string &password, int balance) : name(name), password(password), balance(balance) {}
User::User() : name(""), password(""), balance(0) {}

// Member function implementations
void User::setName(const std::string &newName)
{
    name = newName;
}
void User::setPassword(const std::string &newPassword)
{
    password = newPassword;
}
void User::setBalance(int newBalance)
{
    balance = newBalance;
}

void User::display() const
{
    std::cout << "Name: " << name << std::endl;
}
std::string User::getName()
{
    return name;
}
std::string User::getPassword()
{
    return password;
}
int User::getBalance()
{
    return balance;
}

#endif