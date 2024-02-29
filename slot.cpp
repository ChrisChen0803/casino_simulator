#include "Slot.h"
#include <iostream>

#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

Slot::Slot() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));

    // Initialize the slots with random numbers
    for (int i = 0; i < 3; ++i) {
        slots[i] = rand() % 9 + 1; // Generate a random number between 1 and 9
    }
}
bool isInteger1(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}
void Slot::playslot(int bet, User* user) {
    system("cls");
    std::cout<<"Please choose a target number"<<std::endl;
    std::string input;
    std::cin>>input;
    if(!(isInteger1(input)&&stoi(input)<10&&stoi(input)>0)){
        std::cout << "Invalid Input! Please try again..."<<std::endl;
        playslot(bet,user);
        return;
    }
    int targetNum = stoi(input);
    int balance = user->getBalance();
    balance = balance - bet;
    user->setBalance(balance);
    // Display the current slots
    std::cout << "Current slots: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << slots[i] << " ";
    }
    std::cout << std::endl;
    int winningBet = 0;
    // Check if all slots have the same number
    if (slots[0] == slots[1] && slots[1] == slots[2]) {
        winningBet = bet * bet;
        if(slots[0]==targetNum){
            winningBet = winningBet * 9;
            std::cout << "Congratulations! You guess the right target number and slots are the same! You win " <<winningBet<<"!" << std::endl;
        }
        else{
            std::cout << "Congratulations! Slots are the same and you win " <<winningBet<<"!" << std::endl;
        }
        
    }
    //Two slots are the same
    else if(slots[0]==slots[1]||slots[0]==slots[2]||slots[2]==slots[1]){
        winningBet = bet * 3/4;
        int target = 0;
        for(int i = 0; i<3; i++){
            if(slots[i]==targetNum){
                target = target + 1;
            }
        }
        if(target==0){
            std::cout<<"Two slots are the same, you only win " <<winningBet<<"." << std::endl;
        }
        else if(target==1){
            winningBet = bet * 3/2;
            std::cout<<"Two slots are the same and you guess the target number once, you win " <<winningBet<<"!" << std::endl;
        }
        else{
            winningBet = bet * 5/2;
            std::cout<<"Two slots are the same and you guess the target number twice, you win " <<winningBet<<"!" << std::endl;
        }
    }
    else {
        int target = 0;
        for(int i = 0; i<3; i++){
            if(slots[i]==targetNum){
                target = target + 1;
            }
        }
        if(target==0){
            std::cout << "You lose! Better luck next time!" << std::endl;
        }
        else{
            winningBet = bet/2;
            std::cout<< "You guess the target number once. You get "<<winningBet<<"."<<std::endl;
        }
    }
    balance = balance + winningBet;
    user->setBalance(balance);
    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::cin.get();
}
