#include "user.h"
#include "user.cpp"
#include "slot.h"
#include "slot.cpp"
#include <iostream>
#include <cstdlib>
#include "login.cpp"
#include "guessing.h"
#include "guessing.cpp"
#include "horserace.cpp"
#include <string>
#include <vector>
#include "blackjack.h"
#include "blackjack.cpp"
User user;
Login login;
void showStartScreen();
void mainLogin();
void loginServ()
{
    system("cls");
    std::string username;
    std::string password;
    std::cout << "=====================" << std::endl;
    std::cout << "Login" << std::endl;
    std::cout << "Please enter your name" << std::endl;
    std::cin >> username;
    std::cout << "Please enter your password" << std::endl;
    std::cin >> password;
    bool auth = login.authenticate(username, password);
    std::cout << "-----------------" << std::endl;
    if (auth)
    {
        std::cout << "Login" << std::endl;
        user = login.getUser(username);
        showStartScreen();
    }
    else
    {
        std::cout << "Failed. Please Try Again. Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void registerServ()
{
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout << "Register" << std::endl;
    std::cout << "Please enter username:" << std::endl;
    std::string username;
    std::cin >> username;
    std::cout << "Please enter password:" << std::endl;
    std::string password;
    std::cin >> password;
    if (password.length() < 8)
    {
        std::cout << "Password length should greater or equal to 8! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
        return;
    }
    bool success = login.registerUser(username, password);
    if (success)
    {
        login.saveCredentialsToFile("credentials.txt");
        std::cout << "Register Sucessful! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
    else
    {
        std::cout << "Username already Exist! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void mainLogin()
{
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout << "Welcome to Login Page" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. No Account? Register" << std::endl;
    std::string t;
    std::cin >> t;
    if (t == "1")
    {
        loginServ();
    }
    else if (t == "2")
    {
        registerServ();
    }
    else
    {
        std::cout << "=====================" << std::endl;
        std::cout << "Invalid input, please try again. Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
    }
}
void checkBalance()
{
    std::string username = user.getName();
    int balance = user.getBalance();
    std::cout << "Hi " << username << "! Your balance is " << balance << "." << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    showStartScreen();
}
// Interface for games. Easy to change.
void playGames(std::string game, int bet)
{
    system("cls");
    std::cout << "=====================" << std::endl;
    std::cout << "Welcome to Play " << game << std::endl;
    std::cout << "Current bet:" << bet << std::endl;
    std::cout << "1. Start a new game" << std::endl;
    std::cout << "2. Change the rate" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::string input;
    std::cin >> input;
    if (input == "1")
    {
        int currBalance = user.getBalance();
        if (currBalance < bet)
        {
            std::cout << "Your balance is not enough. Please change the bet" << std::endl;
            std::cout << "Your Balance is " << currBalance << "! Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            playGames(game, bet);
        }
        else
        {
            if (game == "blackJack")
            {
                playBlackjack(bet, &user);
            }
            else if (game == "guessing")
            {
                Guessing guessing(bet);
                guessing.playGuessing(bet, &user);
            }
            else if (game == "slot")
            {
                Slot slot;
                slot.playslot(bet, &user);
            }
            else if (game == "horserace")
            {
                playHorseRace(bet, &user);
            }
            showStartScreen();
        }
        return;
    }
    else if (input == "2")
    {
        std::cout << "Please enter the bet you want to play with" << std::endl;
        std::string b;
        std::cin >> b;
        if (isInteger(b) && std::stoi(b) > 0)
        {
            std::cout << "Change Successful! Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            playGames(game, std::stoi(b));
        }
        else
        {
            std::cout << "Invalid! Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            playGames(game, bet);
        }
        return;
    }
    else if (input == "3")
    {
        std::cout << "GoodBye!" << std::endl;
        showStartScreen();
        return;
    }
    else
    {
        std::cout << "Invalid! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        playGames(game, bet);
    }
}

void changePassword()
{
    system("cls");
    std::string oldPass = user.getPassword();
    std::string password1;
    std::string password2;
    std::cout << "Please type the password you want to change to:" << std::endl;
    std::cin >> password1;
    if (password1.length() < 8)
    {
        std::cout << "Your password should not less than 8 chars." << std::endl;
        std::cout << "Press any key to retry...";
        std::cin.ignore();
        std::cin.get();
        changePassword();
        return;
    }
    else if (password1 == oldPass)
    {
        std::cout << "Your new password should be the same as the old one " << std::endl;
        std::cout << "Press any key to retry...";
        std::cin.ignore();
        std::cin.get();
        changePassword();
        return;
    }
    std::cout << "Please retype your new password" << std::endl;
    std::cin >> password2;
    if (password1 != password2)
    {
        std::cout << "The passwords do not match" << std::endl;
        std::cout << "Press any key to retry...";
        std::cin.ignore();
        std::cin.get();
        changePassword();
        return;
    }
    user.setPassword(password1);
    std::cout << "Successfully Changed your password" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.ignore();
    std::cin.get();
    showStartScreen();
}

void topUpServ()
{
    std::cout << "Please enter how much you want to charge" << std::endl;
    std::string b;
    std::cin >> b;
    if (isInteger(b) && std::stoi(b) > 0)
    {
        if (std::stoi(b) > 10000)
        {
            std::cout << "Sorry The maximum amount of a single top-up is 10000. Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
            topUpServ();
        }
        int balance = user.getBalance();
        balance = balance + std::stoi(b);
        user.setBalance(balance);
        std::cout << "Successful! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        showStartScreen();
    }
    else
    {
        std::cout << "Invalid! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        showStartScreen();
    }
    return;
}

void showStartScreen()
{
    // Clear the screen
    // system("clear"); // For Linux/macOS
    system("cls"); // For Windows
    std::string input;
    // Print the start screen
    std::cout << "Welcome to the Casino! Have Fun!" << std::endl;
    std::cout << "=====================" << std::endl;
    if (user.getName() == "")
    {
        std::cout << "Please Login" << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        mainLogin();
        return;
    }
    login.updateCred(user.getName(), user);
    login.saveCredentialsToFile("credentials.txt");
    std::cout << user.getName() << ", what you wanna do today?" << std::endl;
    std::cout << "1. Play Blackjack" << std::endl;
    std::cout << "2. Play Guessing" << std::endl;
    std::cout << "3. Play Slots" << std::endl;
    std::cout << "4. Play Hourse Betting" << std::endl;
    std::cout << "5. Top Up" << std::endl;
    std::cout << "6. Check Balance" << std::endl;
    std::cout << "7. Change Password" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "=====================" << std::endl;
    std::cout << "Enter your input: ";
    std::cin >> input; // Wait for user input
    std::cout << "You entered: " << input << std::endl;
    if (input == "1")
    {
        playGames("blackJack", 10);
    }
    else if (input == "2")
    {
        playGames("guessing", 10);
    }
    else if (input == "3")
    {
        playGames("slot", 10);
    }
    else if (input == "4")
    {
        playGames("horserace", 10);
    }
    else if (input == "5")
    {
        topUpServ();
    }
    else if (input == "6")
    {
        checkBalance();
    }
    else if (input == "7")
    {
        changePassword();
    }
    else if (input == "8")
    {
        std::cout << "Thanks for visiting! Goodbye." << std::endl;
        return;
    }
    else
    {
        std::cout << "Invalid Input! Press any key to continue..." << std::endl;
        std::cin.ignore();
        std::cin.get();
        showStartScreen();
    }
}
int main()
{
    // int i = user.getBalance();
    // std::string in;
    login.loadCredentialsFromFile("credentials.txt");
    showStartScreen();
}