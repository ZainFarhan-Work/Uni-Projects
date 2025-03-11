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
Battle::Battle(Pokemon &p1, Pokemon &p2)
    : pokemon1(p1), pokemon2(p2)
{
    //Initialize the variables here


    //Donot edit this condition ---------------------------------------------------
    if (!deterministic)
    {
        srand(time(0)); // Uses current time as seed for randomness
    }
}

// simulateRound: Simulate one round of battle
bool Battle::simulateRound()
{
    
}

// simulateFullBattle: Run rounds until the battle is finished
void Battle::simulateFullBattle()
{

}

// getBattleHistory: Return a copy of the battle history
BattleHistory Battle::getBattleHistory() const
{

}

// getWinner: Returns pointer to the winning Pokemon, or nullptr on tie/incomplete
Pokemon *Battle::getWinner() const
{

}

// calculateDamage: Compute damage given attacker, defender and move parameters.


int Battle::calculateDamage(Pokemon &attacker, Pokemon &defender, Move &move)
{

}