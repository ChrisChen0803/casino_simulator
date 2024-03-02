#include "blackjack.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "user.h"
#include "user.cpp"
#include <chrono>
Deck::Deck()
{
    for (int rank = ACE; rank <= KING; ++rank)
    {
        for (int i = 0; i < 4; ++i)
        {
            cards.push_back(rank);
        }
    }
    shuffle();
}

void Deck::shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::shuffle(cards.begin(), cards.end(), g);
}

int Deck::dealCard()
{
    int card = cards.back();
    cards.pop_back();
    return card;
}

int Hand::getValue() const
{
    int value = 0;
    bool hasAce = false;
    for (int card : cards)
    {
        if (card == ACE)
        {
            hasAce = true;
        }
        value += (card > 10 ? 10 : card);
    }
    if (hasAce && value + 10 <= 21)
    {
        value += 10;
    }
    return value;
}

void Hand::printHand() const
{
    for (int card : cards)
    {
        std::cout << card << " ";
    }
    std::cout << std::endl;
}

void Hand::addCard(int card)
{
    cards.push_back(card);
}

bool BlackjackHand::isBusted() const
{
    return getValue() > 21;
}

bool BlackjackHand::hasBlackjack() const
{
    return getValue() == 21 && cards.size() == 2;
}
void playBlackjack(int bet, User *user)
{
    system("cls");
    std::cout << "Welcome to Blackjack!" << std::endl;
    std::cout << "Current bet: " << bet << std::endl;
    int balance = user->getBalance();
    balance = balance - bet;
    user->setBalance(balance);
    Deck deck;
    BlackjackHand playerHand;
    BlackjackHand dealerHand;

    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());
    playerHand.addCard(deck.dealCard());
    dealerHand.addCard(deck.dealCard());

    std::cout << "Your hand: ";
    playerHand.printHand();
    std::cout << "Value: " << playerHand.getValue() << std::endl
              << std::endl;

    std::cout << "Dealer's hand: ";
    std::cout << "Hidden card ";
    dealerHand.printHand();
    std::cout << std::endl;

    while (true)
    {
        char choice;
        std::cout << "Do you want to hit (h) or stand (s)? ";
        std::cin >> choice;
        if (choice == 'h')
        {
            playerHand.addCard(deck.dealCard());
            std::cout << "Your hand: ";
            playerHand.printHand();
            std::cout << "Value: " << playerHand.getValue() << std::endl
                      << std::endl;
            if (playerHand.isBusted())
            {
                std::cout << "Busted! You lose." << std::endl;
                std::cout << "Press any key to continue..."<<std::endl;
                std::cin.ignore();
                std::cin.get();
                return;
            }
        }
        else if (choice == 's')
        {
            break;
        }
        else
        {
            std::cout << "Invalid Input!.Press any key to continue..."<<std::endl;
            std::cin.ignore();
            std::cin.get();
        }
    }

    std::cout << "Dealer's hand: ";
    dealerHand.printHand();
    std::cout << "Value: " << dealerHand.getValue() << std::endl
              << std::endl;

    while (dealerHand.getValue() < 17)
    {
        dealerHand.addCard(deck.dealCard());
        std::cout << "Dealer hits" << std::endl;
        std::cout << "Dealer's hand: ";
        dealerHand.printHand();
        std::cout << "Value: " << dealerHand.getValue() << std::endl
                  << std::endl;
        if (dealerHand.isBusted())
        {
            std::cout << "Dealer busted! You win." << std::endl;
            user->setBalance(balance + 2 * bet);
            std::cout << "Press any key to continue..."<<std::endl;
            std::cin.ignore();
            std::cin.get();
            return;
        }
    }

    if (dealerHand.getValue() > playerHand.getValue())
    {
        std::cout << "Dealer wins." << std::endl;
    }
    else if (dealerHand.getValue() < playerHand.getValue())
    {
        std::cout << "You win." << std::endl;
        user->setBalance(balance + 2 * bet);
    }
    else
    {
        std::cout << "It's a tie." << std::endl;
        user->setBalance(balance + bet);
    }
    std::cout << "Press any key to continue..."<<std::endl;
    std::cin.ignore();
    std::cin.get();
}