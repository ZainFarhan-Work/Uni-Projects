//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Gym.cpp
#include "../include/Gym.hpp"
#include <iostream>
#include <sstream>

// Private expand function
void Gym::expandGym()
{
    // TODO: If you are using a dynamic array to store gym Pokémon,
    // expand the array by allocating a new array with larger capacity,
    // copy the existing pointers, then delete the old array.
    return;
}

// Constructor
Gym::Gym(Trainer *gymLeader, const string &badgeName, int difficulty)
{
    // TODO: Initialize member variables, e.g.,
    // - Set the gym leader pointer.
    // - Save the badge name and difficulty level.
    // - Initialize the storage for gym Pokémon

    this->gymLeader = gymLeader;

    pokemonCount = gymLeader->getPartyCount();
    capacity = gymLeader->getPartyCount();

    this->gymPokemon = new Pokemon*[gymLeader->getPartyCount()];

    for (int i = 0; i < gymLeader->getPartyCount(); i++)
    {
        gymPokemon[i] = gymLeader->getPokemonAtIndex(i);
    }

    this->badgeName = badgeName;
    this->difficulty = difficulty;
    
}

// Destructor
Gym::~Gym()
{
    // TODO: Clean up any dynamically allocated memory if the Gym owns the Pokémon.
    // If the Gym does not own them, be careful not to double-delete.

    delete[] gymPokemon;
}

// Getters
string Gym::getBadgeName() const 
{ 
    return "";
}
int Gym::getDifficulty() const 
{ 
    return -1;
}
int Gym::getPokemonCount() const 
{ 
    return -1;
}
Trainer *Gym::getGymLeader() const 
{ 
    return nullptr;
}
Pokemon *Gym::getGymPokemonAtIndex(int index) const
{
    return nullptr;
}
BattleHistory Gym::getGymHistory() const
{
    // TODO: Return a copy of the gym's BattleHistory
}

// Gym management
void Gym::addGymPokemon(Pokemon *p)
{
    return;
}

bool Gym::removeGymPokemon(int index)
{
    return false;
}

// Battle functionality (There will be hidden test cases for this portion, to test multiple scenarios in both deterministic and non-deterministic methods)
bool Gym::battle(Trainer *challenger)
{
    // Simple simulation: challenger wins if every gym Pokemon is defeated in order to win.
    // For now, this return value is a placeholder.
    // A proper implementation would involve simulating a battle using the Battle class
    // If your test case passes for the correct implementation.
    return false;
}

void Gym::healAllPokemon()
{
    return;
}