#ifndef SLOT_H
#define SLOT_H
#include "user.h"
#include "user.cpp"
class Slot
{
private:
    int slots[3];

public:
    Slot();                             // Constructor
    void playslot(int bet, User *user); // Play the slot game
};

#endif // SLOT_H
