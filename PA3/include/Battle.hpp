#ifndef BATTLE_HPP
#define BATTLE_HPP

#include <string>
#include "Pokemon.hpp"
#include "BattleHistory.hpp"
using namespace std;

class Battle
{
private:
    Pokemon &pokemon1;  
    Pokemon &pokemon2;
    BattleHistory history;
    bool isFinished;
    Pokemon *winner;
    int currentRound;
    static const int MAX_ROUNDS = 20;

public:
    // For testing - enables deterministic battle results
    static bool deterministic;

    // Constructor
    Battle(Pokemon &p1, Pokemon &p2);

    // Battle functions
    bool simulateRound();       // Simulates a single round of battle
    void simulateFullBattle();  // Simulates until a Pokemon faints or MAX_ROUNDS
    bool isComplete() const;    // Check if battle is complete
    Pokemon *getWinner() const; // Get winner (nullptr if no winner yet)
    int getCurrentRound() const;

    // Log access
    BattleHistory getBattleHistory() const;
    void printBattleLog() const;

    // Calculate damage (factoring in type advantages, armor, etc.)
    int calculateDamage(Pokemon &attacker, Pokemon &defender, Move &move);
};

#endif