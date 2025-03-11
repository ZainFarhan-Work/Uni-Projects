#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <string>
using namespace std;

class Armor
{
private:
    string name;
    int defenseBonus;
    double weight;

public:
    // Constructors
    Armor();
    Armor(const string &n, int def, double w);

    // Copy constructor and assignment operator
    Armor(const Armor &other);
    void copyFrom(const Armor &other);

    // Getters
    string getName() const;
    int getDefenseBonus() const;
    double getWeight() const;

    // Functionality
    bool isHeavy() const; // Returns true if weight > 10.0
};

#endif