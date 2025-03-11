#ifndef TRAINER_HPP
#define TRAINER_HPP

#include <string>
#include "Pokemon.hpp"
#include "Potion.hpp"
using namespace std;

class Trainer
{
private:
    string name;
    Pokemon **party; // Dynamic array of Pokemon pointers
    int partyCount;
    int partyCapacity;
    Potion *potions; // Dynamic array of potions
    int potionCount;
    int potionCapacity;
    int money; // Currency for buying items

    void expandParty();
    void expandPotions();

public:
    // Constructors
    Trainer();
    Trainer(const string &n);

    // Copy constructor, assignment function, and destructor
    Trainer(const Trainer &other);
    void copyFrom(const Trainer &other);
    ~Trainer();

    // Getters
    string getName() const;
    int getPartyCount() const;
    int getPotionCount() const;
    int getMoney() const;
    Pokemon *getPokemonAtIndex(int index) const;
    Potion *getPotionAtIndex(int index) const;

    // Pokemon management
    bool addPokemon(Pokemon *p);
    bool removePokemon(int index); // Removes Pokemon from party (doesn't delete)
    bool hasPokemon(const string &name) const;
    Pokemon *getFirstNonFaintedPokemon() const;

    // Potion management
    bool addPotion(const Potion &p);
    bool removePotion(int index);
    bool usePotion(int potionIndex, int pokemonIndex);

    // Money management
    void addMoney(int amount);
    bool spendMoney(int amount); // Returns false if not enough money
};

#endif