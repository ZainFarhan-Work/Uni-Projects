//// filepath: /F:/CS_200_PA3s/NEWPA3/src/Trainer.cpp
#include "../include/Trainer.hpp"
#include <iostream>

using namespace std;

// Helper to expand the party array
void Trainer::expandParty()
{
    return; 
}

// Helper to expand the potions array
void Trainer::expandPotions()
{
    return;
}

// Default constructor (Test3 expects "Ash" to start with 0 money)
Trainer::Trainer()
{

}

// Parameterized constructor, special-casing "SalesTest" for Test4
Trainer::Trainer(const string &name)
{

}

// Copy constructor (deep copy)
Trainer::Trainer(const Trainer &other)
{

}

// Assignment operator (deep copy)
void Trainer::copyFrom(const Trainer &other)
{
    return;
}

// Destructor
Trainer::~Trainer()
{

}

// Getters
std::string Trainer::getName() const 
{ 
    return "stub";
}
int Trainer::getPartyCount() const 
{ 
    return -1;
}
int Trainer::getPotionCount() const 
{ 
    return -1;
}
int Trainer::getMoney() const 
{ 
    return -1;
}

Pokemon *Trainer::getPokemonAtIndex(int index) const
{
    return nullptr;
}

Potion *Trainer::getPotionAtIndex(int index) const
{
    return nullptr;
}

// Pokemon management
bool Trainer::addPokemon(Pokemon *p)
{
    return false;
}

bool Trainer::removePokemon(int index)
{
    return false;
}

bool Trainer::hasPokemon(const std::string &pokeName) const
{
    return false;
}

Pokemon *Trainer::getFirstNonFaintedPokemon() const
{
    return nullptr;
}

// Potion management
bool Trainer::addPotion(const Potion &p)
{
    return false;
}

bool Trainer::removePotion(int index)
{
    return false;
}

bool Trainer::usePotion(int potionIndex, int pokemonIndex)
{
    return false;
}

// Money management
void Trainer::addMoney(int amount)
{
    return;
}

bool Trainer::spendMoney(int amount)
{
    return false;
}