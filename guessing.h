#ifndef GUESSING_H
#define GUESSING_H
#include "user.h"
#include "user.cpp"
#include <iostream>
#include <vector>
class Guessing
{
private:
    std::vector<int> pool;

public:
    Guessing(int bet);                      // Constructor
    void playGuessing(int bet, User *user); // Play the slot game
};

#endif
