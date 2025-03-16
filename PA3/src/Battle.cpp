/// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Battle.cpp
#include "../include/Battle.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;



bool Battle::deterministic = true; // (Flag for testing, set to false for randomness, true for deterministic)

/*
    Ideally your battle class should be able to simulate a full battle between two Pokemon in both scenarios (deterministic & non-deterministic). 
    But for the case of simplicity, we will only implement the deterministic version of the battle class to make sure you win every battle
    BUT
    YOU MUST IMPLEMENT A NON DETERMINISTIC version of the battle for which a random seed is initialized within the constructors, which means you must pass the test sometimes and fail the test
    sometimes randomly.

    For the testing procedure, we will test the deterministic version of the battle class, and then we will test the non-deterministic version of the battle class.
    The deterministic version of the battle class should always pass the tests, and the non-deterministic version of the battle class should sometimes pass the tests and sometimes fail the tests.
*/

// Constructor
Battle::Battle(Pokemon &p1, Pokemon &p2) : pokemon1(p1), pokemon2(p2)
{
    //Initialize the variables here

    isFinished = false;
    winner = new Pokemon;
    currentRound = 0;


    //Donot edit this condition ---------------------------------------------------
    if (!deterministic)
    {
        srand(time(0)); // Uses current time as seed for randomness
    }
}

// simulateRound: Simulate one round of battle
bool Battle::simulateRound()
{
    if (pokemon1.isFainted() && pokemon2.isFainted())
    {
        return false;
    }

    currentRound++;

    if (currentRound > MAX_ROUNDS)
    {
        delete winner;
        winner = NULL;

        return false;
    }
    

    Move move;

    // First Pokemon Attacks

    for (int i = 0; i < pokemon1.getMoveCount(); i++)
    {
        if (pokemon1.getMoveAtIndex(i)->getPP() > 0)
        {
            move = *(pokemon1.getMoveAtIndex(i));
        }
        
    }
    
    pokemon2.takeDamage(calculateDamage(pokemon1, pokemon2, move));
    string log = "";
    log += to_string(currentRound)  + ": " + pokemon1.getName();
    log += " deals " + to_string(calculateDamage(pokemon1, pokemon2, move));
    log += " damage to " + pokemon2.getName() + " (HP: " + to_string(pokemon2.getCurrentHP()) + ")";

    history.addLog(log);

    if (pokemon2.isFainted())
    {
        winner = &pokemon1;
        history.addLog(pokemon1.getName() + " Wins");
        return true;
    }
    
    // Second Pokemon Attacks

    move = Move();

    for (int i = 0; i < pokemon2.getMoveCount(); i++)
    {
        if (pokemon2.getMoveAtIndex(i)->getPP() > 0)
        {
            move = *(pokemon2.getMoveAtIndex(i));
        }
        
    }
    
    pokemon1.takeDamage(calculateDamage(pokemon2, pokemon1, move));
    log = "";
    log += to_string(currentRound)  + ": " + pokemon2.getName();
    log += " deals " + to_string(calculateDamage(pokemon2, pokemon1, move));
    log += " damage to " + pokemon1.getName() + " (HP: " + to_string(pokemon1.getCurrentHP()) + ")";

    history.addLog(log);

    if (pokemon1.isFainted())
    {
        winner = &pokemon2;
        history.addLog(pokemon2.getName() + " Wins");
        return true;
    }
    
    return false;
    
}

// simulateFullBattle: Run rounds until the battle is finished
void Battle::simulateFullBattle()
{
    for (int i = 0; i < MAX_ROUNDS; i++)
    {
        if (simulateRound())
        {
            break;
        }   
    }

}

// getBattleHistory: Return a copy of the battle history
BattleHistory Battle::getBattleHistory() const
{
    return history;
}

// getWinner: Returns pointer to the winning Pokemon, or nullptr on tie/incomplete
Pokemon *Battle::getWinner() const
{
    return winner;
}

// calculateDamage: Compute damage given attacker, defender and move parameters.

int Battle::calculateDamage(Pokemon &attacker, Pokemon &defender, Move &move)
{
    return 10; // Placeholder Value

}