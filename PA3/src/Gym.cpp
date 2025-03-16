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

    // Resize Array
    Pokemon** temp = gymPokemon;

    gymPokemon = new Pokemon*[capacity * 2];

    // Copying data from Old Array into New

    for (int i = 0; i < pokemonCount - 1; i++)
    {
        gymPokemon[i] = temp[i];
    }

    delete[] temp;

    capacity *= 2;

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

    pokemonCount = 0;
    capacity = 1;

    this->gymPokemon = new Pokemon*[1];

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
    return badgeName;
}
int Gym::getDifficulty() const 
{ 
    return difficulty;
}
int Gym::getPokemonCount() const 
{ 
    return pokemonCount;
}
Trainer *Gym::getGymLeader() const 
{ 
    return gymLeader;
}
Pokemon *Gym::getGymPokemonAtIndex(int index) const
{
    return gymPokemon[index];
}
BattleHistory Gym::getGymHistory() const
{
    // TODO: Return a copy of the gym's BattleHistory
    return gymHistory;
}

// Gym management
void Gym::addGymPokemon(Pokemon *p)
{
    if (++pokemonCount > capacity)
    {
        expandGym();
    }

    gymPokemon[pokemonCount - 1] = p;
    
    return;
}

bool Gym::removeGymPokemon(int index)
{
    if (index > pokemonCount - 1)
    {
        return false;
    }

    for (int i = index; i < pokemonCount - 1; i++)
    {
        gymPokemon[i] = gymPokemon[i + 1];
    }

    pokemonCount--;

    return true;
}

// Battle functionality (There will be hidden test cases for this portion, to test multiple scenarios in both deterministic and non-deterministic methods)
bool Gym::battle(Trainer *challenger)
{
    // Simple simulation: challenger wins if every gym Pokemon is defeated in order to win.
    // For now, this return value is a placeholder.
    // A proper implementation would involve simulating a battle using the Battle class
    // If your test case passes for the correct implementation.

    while (true)
    {
        Pokemon *gymP = gymLeader->getFirstNonFaintedPokemon();
        Pokemon *challengerP = challenger->getFirstNonFaintedPokemon();

        // Challenger Wins
        if (gymP == nullptr)
        {
            string his = gymHistory.getAllLogs();
            cout << his << endl;
            return true;
        }
        
        // Gym Wins
        if (challengerP == nullptr)
        {
            return false;
        }
        
        Battle battle(*gymP, *challengerP);
        battle.simulateFullBattle();

        for (int i = 0; i < battle.getBattleHistory().getLogCount(); i++)
        {
            gymHistory.addLog(battle.getBattleHistory().getLogAt(i));
        }
                
    }

    return false;
}

void Gym::healAllPokemon()
{
    for (int i = 0; i < pokemonCount; i++)
    {
        // Fully Heals all Pokemon
        gymPokemon[i]->resetHP();
    }
    
    return;
}