#ifndef GYM_HPP
#define GYM_HPP

#include <string>
#include "Trainer.hpp"
#include "Pokemon.hpp"
#include "Battle.hpp"
using namespace std;

class Gym
{
private:
    Trainer *gymLeader;   // The gym leader
    Pokemon **gymPokemon; // Dynamic array of Pokemon pointers for battles
    int pokemonCount;
    int capacity;
    string badgeName;         // Name of badge awarded for beating gym
    int difficulty;           // Determines base power of gym Pokemon
    BattleHistory gymHistory; // History of all battles in this gym

    void expandGym();

public:
    // Constructors and destructor
    Gym(Trainer *leader, const string &badge = "Badge", int diff = 1);
    ~Gym();

    // No copy constructor or assignment - gym is unique

    // Getters
    string getBadgeName() const;
    int getDifficulty() const;
    int getPokemonCount() const;
    Trainer *getGymLeader() const;
    Pokemon *getGymPokemonAtIndex(int index) const;
    BattleHistory getGymHistory() const;

    // Gym management
    void addGymPokemon(Pokemon *p);
    bool removeGymPokemon(int index);

    // Battle functionality
    bool battle(Trainer *challenger); // Returns true if challenger beats all gym Pokemon
    void healAllPokemon();            // Restore all gym Pokemon to full health
};

#endif