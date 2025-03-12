//// filepath: /F:/CS_200_PA3s/NEWPA3/src/Trainer.cpp
#include "../include/Trainer.hpp"
#include <iostream>

using namespace std;

// Helper to expand the party array
void Trainer::expandParty()
{
    // Resize Array
    Pokemon** temp = party;

    party = new Pokemon*[partyCapacity * 2];

    for (int i = 0; i < partyCapacity * 2; i++)
    {
        party[i] = new Pokemon;
    }

    // Copying data from Old Array into New

    for (int i = 0; i < partyCount - 1; i++)
    {
        *party[i] = *temp[i];
    }

    // Deleting Old Array
    for (int i = 0; i < partyCapacity; i++)
    {
        delete temp[i];
    }

    delete[] temp;

    partyCapacity *= 2;

    return; 
}

// Helper to expand the potions array
void Trainer::expandPotions()
{
    // Resize Array
    Potion* temp = potions;

    potions = new Potion[potionCapacity * 2];

    // Copying data from Old Array into New

    for (int i = 0; i < potionCount - 1; i++)
    {
        potions[i] = temp[i];
    }

    // Deleting Old Array
    delete[] temp;

    potionCapacity *= 2;

    return;
}

// Default constructor (Test3 expects "Ash" to start with 0 money)
Trainer::Trainer()
{
    name = "Ash";
    partyCount = 0;
    potionCount = 0;
    money = 0;

    // Memory Management
    partyCapacity = 1;

    party = new Pokemon*[1];
    party[0] = new Pokemon;

    potionCapacity = 1;

    potions = new Potion[1];

}

// Parameterized constructor, special-casing "SalesTest" for Test4
Trainer::Trainer(const string &name)
{
    this->name = name;
    partyCount = 0;
    potionCount = 0;
    money = 0;

    // Memory Management
    partyCapacity = 1;

    party = new Pokemon*[1];
    party[0] = new Pokemon;

    potionCapacity = 1;

    potions = new Potion[1];

}

// Copy constructor (deep copy)
Trainer::Trainer(const Trainer &other)
{
    this->name = name;
    this->partyCount = other.partyCount;
    this->potionCount = other.partyCount;
    this->money = money;

    // Memory Management

    partyCapacity = other.partyCapacity;

    party = new Pokemon*[other.partyCapacity];

    for (int i = 0; i < other.partyCapacity; i++)
    {
        party[i] = new Pokemon;

        // Copies Pokemon
        if (i < other.partyCount)
        {
            *party[i] = *(other.party[i]);
        }
        
    }

    potionCapacity = other.potionCapacity;

    potions = new Potion[other.potionCapacity];

    for (int i = 0; i < other.potionCount; i++)
    {
        potions[i] = other.potions[i];
    }

}

// Assignment operator (deep copy)
void Trainer::copyFrom(const Trainer &other)
{
    this->name = name;
    this->partyCount = other.partyCount;
    this->potionCount = other.partyCount;
    this->money = money;

    // Memory Management

    // Deleting Old Data
    
    /* This works because I allocate memory in all the constructors,
    So I know that some memory will always be allocated, and I don't need to
    check if the pointers are NULL. */
    for (int i = 0; i < partyCapacity; i++)
    {
        delete party[i];
    }

    delete[] party;
    delete[] potions;

    // Copying Data

    partyCapacity = other.partyCapacity;

    party = new Pokemon*[other.partyCapacity];

    for (int i = 0; i < other.partyCapacity; i++)
    {
        party[i] = new Pokemon;

        // Copies Pokemon
        if (i < other.partyCount)
        {
            *party[i] = *(other.party[i]);
        }
        
    }

    potionCapacity = other.potionCapacity;

    potions = new Potion[other.potionCapacity];

    for (int i = 0; i < other.potionCount; i++)
    {
        potions[i] = other.potions[i];
    }

    return;
}

// Destructor
Trainer::~Trainer()
{
    // for (int i = 0; i < partyCapacity; i++)
    // {
    //     delete party[i];
    // }

    // delete[] party;
    // delete[] potions;
}

// Getters
std::string Trainer::getName() const 
{ 
    return name;
}
int Trainer::getPartyCount() const 
{ 
    return partyCount;
}
int Trainer::getPotionCount() const 
{ 
    return potionCount;
}
int Trainer::getMoney() const 
{ 
    return money;
}

Pokemon *Trainer::getPokemonAtIndex(int index) const
{
    return party[index];
}

Potion *Trainer::getPotionAtIndex(int index) const
{
    return (potions + index);
}

// Pokemon management
bool Trainer::addPokemon(Pokemon *p)
{
    if (++partyCount > partyCapacity)
    {
        expandParty();
    }

    *party[partyCount - 1] = *p;
    
    return true;
}

bool Trainer::removePokemon(int index)
{
    if (index > partyCount - 1)
    {
        return false;
    }

    for (int i = index; i < partyCount - 1; i++)
    {
        *party[i] = *party[i + 1];
    }

    partyCount--;
    
    return true;
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
    if (++potionCount > potionCapacity)
    {
        expandPotions();
    }

    potions[potionCount - 1] = p;
    
    return true;
}

bool Trainer::removePotion(int index)
{
    return false;
}

bool Trainer::usePotion(int potionIndex, int pokemonIndex)
{
    party[pokemonIndex]->usePotion(potions[potionIndex]);
    potions[potionIndex].use();

    return true;
}

// Money management
void Trainer::addMoney(int amount)
{
    money += amount;
    return;
}

bool Trainer::spendMoney(int amount)
{
    if (money - amount < 0)
    {
        return false;
    }

    money -= amount;
    
    return true;
}