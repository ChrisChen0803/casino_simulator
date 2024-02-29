#include "guessing.h"
#include <iostream>
#include <algorithm> 
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()


Guessing::Guessing(int bet) {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr)));
    pool = {0,0,0,0,0};
    // Initialize the slots with random numbers
    int sum = 5 * bet;
    for (int i = 0; i < 5; ++i) {
        int curr = rand() % (3*bet+1);
        if(sum==0){
            pool[i] = 0;
        }
        else if(sum<curr){
            pool[i] = sum;
            sum = 0;
        }
        else{
            pool[i] = curr;
            sum = sum - curr;
        }
    }
    if(sum!=0){
        pool[4] = pool[4] + sum;
        sum = 0;
    }
}
bool isInteger2(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}
void Guessing::playGuessing(int bet, User* user){
    std::vector<int> sortedPool(pool.begin(), pool.end());
    std::sort(sortedPool.begin(),sortedPool.end());
    std::cout<<"Welcome! The Pool has following rewards:"<<std::endl;
    for(auto reward:sortedPool){
        std::cout<<reward<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Please choose a number from 1 to 5:"<<std::endl;
    std::string input;
    std::cin>>input;
    if(!(isInteger2(input)&&stoi(input)<=5&&stoi(input)>0)){
        std::cout << "Invalid Input! Please try again..."<<std::endl;
        playGuessing(bet,user);
        return;
    }
    int balance = user->getBalance();
    balance = balance - bet;
    user->setBalance(balance);
    int targetNum = stoi(input) - 1;
    int winningbet = pool[targetNum];
    std::cout<<"Congratulations! You win "<<winningbet<<"!"<<std::endl;
    balance = balance + winningbet;
    user->setBalance(balance);
    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::cin.get();
}