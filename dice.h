#ifndef DICE_H
#define DICE_H

#include <cstdlib>

class Dice 
{
private:
    int myRollCount;

public:
    Dice() : myRollCount(0) {}

    int roll() 
    {
        myRollCount++;
        return rand() % 6 + 1;
    }

    int numRolls() const 
    {
        return myRollCount;
    }
};

#endif