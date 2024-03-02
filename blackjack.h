#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

enum Rank
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN = 10,
    JACK = 10,
    QUEEN = 10,
    KING = 10
};

class Deck
{
private:
    std::vector<int> cards;

public:
    Deck();
    void shuffle();
    int dealCard();
};

class Hand
{
protected:
    std::vector<int> cards;

public:
    void addCard(int card);
    int getValue() const;
    void printHand() const;
};

class BlackjackHand : public Hand
{
public:
    bool isBusted() const;
    bool hasBlackjack() const;
};

#endif
