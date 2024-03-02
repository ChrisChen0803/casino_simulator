#include "horserace.h"
#include "user.cpp"
#include "isInteger.cpp"
#include "vector"
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
using namespace std;
HorseRace::HorseRace(int length = 10, int horseNum = 8)
{
    trackLength = length;
    for (int i = 0; i < horseNum; i++)
    {
        horses.push_back(0);
    }
}
void HorseRace::printRaceState()
{
    cout << "D";
    for (int i = 0; i < trackLength; i++)
    {
        cout << " ";
        cout << i + 1;
        cout << " ";
    }
    cout << endl;
    for (int i = 0; i < (int)horses.size(); i++)
    {
        cout << i + 1;
        int dist = horses[i];
        for (int j = 0; j < trackLength; j++)
        {
            if (j == dist)
            {
                cout << " ";
                cout << i + 1;
                cout << " ";
            }
            else
            {
                cout << "===";
            }
        }
        cout << endl;
    }
}
void HorseRace::run(int ind)
{
    horses[ind] += 1;
}

bool HorseRace::hasWinner()
{
    for (int i = 0; i < (int)horses.size(); i++)
    {
        if (horses[i] == trackLength - 1)
        {
            return true;
        }
    }
    return false;
}
int HorseRace::determineWinner()
{
    for (int i = 0; i < (int)horses.size(); i++)
    {
        if (horses[i] == trackLength - 1)
        {
            return i + 1;
        }
    }
    return 0;
}
vector<int> HorseRace::determineSecond()
{
    vector<int> res;
    int max = 0;
    for (int i = 0; i < (int)horses.size(); i++)
    {
        if (max < horses[i] && horses[i] != trackLength - 1)
        {
            max = horses[i];
            res.clear();
            res.push_back(i+1);
        }
        else if (max == horses[i])
        {
            res.push_back(i+1);
        }
    }
    return res;
}
vector<int> HorseRace::determineLast()
{
    vector<int> res;
    int min = trackLength+1;
    for (int i = 0; i < (int)horses.size(); i++)
    {
        if (min > horses[i])
        {
            min = horses[i];
            res.clear();
            res.push_back(i+1);
        }
        else if (min == horses[i])
        {
            res.push_back(i+1);
        }
    }
    return res;
}
void playHorseRace(int bet, User *user)
{
    system("cls");
    HorseRace horserace;
    int first;
    string f;
    int second;
    string s;
    int last;
    string l;
    cout << "Welcome to Horse Racing Bet!" << endl;
    cout << "Please Guess the Champion (1-8):" << endl;
    cin >> f;
    if (!(isInteger(f) && stoi(f) <= 8 && stoi(f) > 0))
    {
        cout << "Invalid Input. Please Try Again" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
        playHorseRace(bet, user);
        return;
    }
    first = stoi(f);
    cout << "Please Guess the Second-Place Horse (1-8):" << endl;
    cin >> s;
    if (!(isInteger(s) && stoi(s) <= 8 && stoi(s) > 0))
    {
        cout << "Invalid Input. Please Try Again" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
        playHorseRace(bet, user);
        return;
    }
    second = stoi(s);
    cout << "Please Guess the Horse Comes in Last (1-8):" << endl;
    cin >> l;
    if (!(isInteger(l) && stoi(l) <= 8 && stoi(l) > 0))
    {
        cout << "Invalid Input. Please Try Again" << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
        playHorseRace(bet, user);
        return;
    }
    last = stoi(l);
    int balance = user->getBalance();
    balance = balance - bet;
    user->setBalance(balance);
    cout << "Game Start!" << endl;
    cout << "Press any key to continue..." << endl;
    cin.ignore();
    cin.get();
    bool hasWinner = false;
    int counter = 0;
    while (!hasWinner)
    {
        counter = counter + 1;
        int run = rand() % 8;
        cout << "Time " << counter << ":" << endl;
        cout << "Horse " << run + 1 << " is running!" << endl;
        horserace.run(run);
        horserace.printRaceState();
        hasWinner = horserace.hasWinner();
        cout << hasWinner << endl;
        cout << "Press any key to continue..." << endl;
        cin.ignore();
        cin.get();
    }
    int winningBet = 0;
    int winner = horserace.determineWinner();
    cout << "Game End! The winner is Horse " << winner << "!" << endl;
    vector<int> sec = horserace.determineSecond();
    cout << "The second place is(are) Horse ";
    for (auto n : sec)
    {
        cout << n;
    }
    cout << "!" << endl;
    vector<int> lst = horserace.determineLast();
    cout << "The last place is(are) Horse ";
    for (auto n : lst)
    {
        cout << n;
    }
    cout << "!" << endl;
    if (winner == first)
    {
        winningBet += 4 * bet;
        cout << "Congrats! You guess the right champion!" << endl;
    }
    auto secPointer = std::find(sec.begin(), sec.end(), second);
    if (secPointer != sec.end())
    {
        winningBet += 2 * bet;
        cout << "Congrats! You guess the right second-place horse!" << endl;
    }
    auto lstPointer = std::find(lst.begin(), lst.end(), last);
    if (lstPointer != lst.end())
    {
        winningBet += bet;
        cout << "Congrats! You guess the right last-place horse!" << endl;
    }
    cout << "You win $" << winningBet << " in total." << endl;
    balance = balance + winningBet;
    user->setBalance(balance);
    cout << "Press any key to continue..." << endl;
    cin.ignore();
    cin.get();
}