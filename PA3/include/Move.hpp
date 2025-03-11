#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>
using namespace std;

class Move
{
private:
    string name;
    int power;    // Damage power
    int accuracy; // Percentage chance to hit (0-100)
    int pp;       // Remaining uses
    int maxPP;    // Maximum possible uses

public:
    // Constructors
    Move();
    Move(const string &n, int pwr, int acc, int uses);

    // Copy constructor and assignment operator
    Move(const Move &other);

    // Getters
    string getName() const;
    int getPower() const;
    int getAccuracy() const;
    int getPP() const;
    int getMaxPP() const;

    // Functionality
    bool use();             // Returns true if move was used successfully (has PP)
    void restore();         // Restore PP to max
    bool isOutOfPP() const; // Check if move is out of PP
};

#endif