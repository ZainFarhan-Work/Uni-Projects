#ifndef POTION_HPP
#define POTION_HPP

#include <string>
using namespace std;

class Potion
{
private:
    string name;
    int healAmount;
    int cost;
    bool isUsed; // Track if potion has been used

public:
    // Constructors
    Potion();
    Potion(const string &n, int heal, int c);

    // Copy constructor and assignment function
    Potion(const Potion &other);

    // Getters
    string getName() const;
    int getHealAmount() const;
    int getCost() const;
    bool getIsUsed() const;

    // Functionality
    void use();          // Mark potion as used
    bool canUse() const; // Check if potion can be used
};

#endif