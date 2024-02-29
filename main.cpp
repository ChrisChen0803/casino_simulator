#include "user.h"
#include "user.cpp"
#include "slot.h"
#include "slot.cpp"
#include <iostream>
#include <cstdlib>
#include "login.cpp"
#include "guessing.h"
#include "guessing.cpp"
#include <string>
#include <vector>
User user;
Login login;
void showStartScreen();
void mainLogin();
void loginServ(){
    system("cls");
    std::string username;
    std::string password;
    std::cout << "=====================" << std::endl;
    std::cout << "Login" << std::endl;
    std::cout << "Please enter your name" << std::endl;
    std::cin>>username;
    std::cout << "Please enter your password" << std::endl;
    std::cin>>password;
    bool auth = login.authenticate(username,password);
    std::cout<<"-----------------"<<std::endl;
    if(auth){
        std::cout << "Login" << std::endl;
        user = login.getUser(username);
        showStartScreen();
    }
    else{
        std::cout<<"Failed. Please Try Again. Press any key to continue..."<<std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void registerServ(){
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout<<"Register"<<std::endl;
    std::cout<<"Please enter username:"<<std::endl;
    std::string username;
    std::cin>>username;
    std::cout<<"Please enter password:"<<std::endl;
    std::string password;
    std::cin>>password;
    if(password.length()<8){
        std::cout<<"Password length should greater or equal to 8! Press any key to continue..."<<std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
        return;
    }
    bool success = login.registerUser(username,password);
    if(success){
        login.saveCredentialsToFile("credentials.txt");
        std::cout<<"Register Sucessful! Press any key to continue..."<<std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
    else{
        std::cout<<"Username already Exist! Press any key to continue..."<<std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void mainLogin(){
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout<<"Welcome to Login Page"<<std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. No Account? Register" << std::endl;
    std::string t;
    std::cin>>t;
    if(t=="1"){
        loginServ();
    }
    else if(t=="2"){
        registerServ();
    }
    else{
        std::cout << "=====================" << std::endl;
        std::cout<<"Invalid input, please try again. Press any key to continue..."<<std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void checkBalance(){
    std::string username = user.getName();
    int balance = user.getBalance();
    std::cout<<"Hi "<<username<<"! Your balance is "<<balance<<"."<<std::endl;
    std::cout << "Press any key to continue...";
    std::cin.ignore();
    std::cin.get();
    showStartScreen();
}
bool isInteger(const std::string& s) {
    try {
        std::stoi(s);
        return true;
    } catch (const std::invalid_argument&) {
        return false;
    } catch (const std::out_of_range&) {
        return false;
    }
}
void playBlackJack(int bet){
    std::vector<int> player_card_list = {};
    std::vector<int> comp_card_list = {};
}
void playGames(std::string game, int bet){
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout << "Welcome to Play " << game << std::endl;
    std::cout << "Current bet:" <<bet<<std::endl;
    std::cout << "1. Start a new game" << std::endl;
    std::cout << "2. Change the rate" << std::endl;
    std::cout << "3. Exit"<<std::endl;
    std::string input;
    std::cin>>input;
    if(input=="1"){
        int currBalance = user.getBalance();
        if(currBalance<bet){
            std::cout << "Your balance is not enough. Please change the bet"<<std::endl;
            std::cout<<"Your Balance is "<<currBalance<<"! Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            playGames(game,bet);
        }
        else{
            if(game=="blackJack"){
                playBlackJack(bet);
            }
            else if(game=="guessing"){
                Guessing guessing(bet);
                guessing.playGuessing(bet,&user);
            }
            else if(game=="slot"){
                Slot slot;
                slot.playslot(bet,&user);
            }
            
            showStartScreen();
        }
        return;
    }
    else if(input=="2"){
        std::cout << "Please enter the bet you want to play with" <<std::endl;
        std::string b;
        std::cin>>b;
        if(isInteger(b)&&std::stoi(b)>0){
            std::cout << "Change Successful! Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            playGames(game,std::stoi(b));
        }
        else{
            std::cout << "Invalid! Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            playGames(game,bet);
        }
        return;
    }
    else if(input=="3"){
        std::cout<<"GoodBye!"<<std::endl;
        showStartScreen();
        return;
    }
    else{
        std::cout << "Invalid! Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        playGames(game,bet);
    }

}


void showStartScreen() {
    // Clear the screen
    //system("clear"); // For Linux/macOS
    system("cls"); // For Windows
    std::string input;
    // Print the start screen
    std::cout << "Welcome to the Casino!" << std::endl;
    std::cout << "=====================" << std::endl;
    if(user.getName()==""){
        std::cout << "Please Login"<<std::endl;
        std::cout << "Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        mainLogin();
        return;
    }
    login.updateCred(user.getName(),user);
    login.saveCredentialsToFile("credentials.txt");
    std::cout << "1. Play Blackjack" << std::endl;
    std::cout << "2. Play Guessing" << std::endl;
    std::cout << "3. Play Slots" << std::endl;
    std::cout << "4. Check Balance" <<std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "Enter your input: ";
    std::cin >> input; // Wait for user input
    std::cout << "You entered: " << input << std::endl;
    if(input=="1"){
        playGames("blackJack",10);
    }
    else if(input=="2"){
        playGames("guessing",10);
    }
    else if(input=="3"){
        playGames("slot",10);
    }
    else if(input=="4"){
        checkBalance();
    }
    else if(input=="5"){
        std::cout<<"Thanks for visiting! Goodbye."<<std::endl;
        return;
    }
    else{
        std::cout << "Invalid Input! Press any key to continue...";
        std::cin.ignore();
        std::cin.get();
        showStartScreen();
    }
}
int main(){
    //int i = user.getBalance();
    //std::string in;
    login.loadCredentialsFromFile("credentials.txt");
    showStartScreen();
}