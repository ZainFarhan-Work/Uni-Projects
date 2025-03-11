#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include "Move.hpp"
#include "Armor.hpp"
#include "Potion.hpp"
using namespace std;

class Pokemon
{
private:
    string name;
    string type;
    int maxHP;
    int currentHP;
    Move *moves; // Dynamic array of moves
    int moveCount;
    int moveCapacity;
    Armor *equippedArmor; // Pokemon can equip one armor
    bool fainted;         // Track if Pokemon has fainted

    void expandMoves();

public:
    // Constructors
    Pokemon();
    Pokemon(const string &n, const string &t, int hp);

    // Copy constructor, assignment operator, and destructor
    Pokemon(const Pokemon &other);
    void copyFrom(const Pokemon &other);
    ~Pokemon();

    // Getters
    string getName() const;
    string getType() const;
    int getMaxHP() const;
    int getCurrentHP() const;
    int getMoveCount() const;
    bool isFainted() const;
    Move *getMoveAtIndex(int index);
    Armor *getEquippedArmor() const;

    // Move management
    bool addMove(const Move &m);
    bool removeMove(int index);
    bool hasMove(const string &moveName) const;

    // Battle functionality
    void takeDamage(int amount);
    void heal(int amount);
    void equipArmor(const Armor &a);
    void removeArmor();
    bool useMove(int moveIndex); // Uses PP
    bool usePotion(const Potion &p);
    void resetHP(); // Reset HP to max
};

#endif