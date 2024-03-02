#ifndef HORSE_RACE_H
#define HORSE_RACE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

class HorseRace
{
private:
    std::vector<int> horses;
    int trackLength;
    std::vector<int> positions;
    int winningHorseIndex;

public:
    HorseRace(int length, int horseNum);

    void printRaceState();

    void run(int ind);

    bool hasWinner();

    int determineWinner();

    std::vector<int> determineSecond();

    std::vector<int> determineLast();

    int getTrackLength() const { return trackLength; }
};

#endif // HORSE_RACE_H