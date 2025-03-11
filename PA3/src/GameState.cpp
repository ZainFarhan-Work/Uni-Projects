//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/GameState.cpp
#include "../include/GameState.hpp"
#include <iostream>

// Constructor
GameState::GameState(Trainer *p, Gym *g, Shop *s)
{

}

// Destructor
GameState::~GameState()
{
    // We may or may not own these pointers. If we do, we delete them:
    // delete player;
    // delete currentGym;
    // delete shop;
}

// Getters
Trainer *GameState::getPlayer() const 
{ 

}
Gym *GameState::getCurrentGym() const 
{ 

}
Shop *GameState::getShop() const 
{ 

}
int GameState::getBadges() const 
{ 
    return -1;
}
string GameState::getPlayerName() const 
{ 
    return "stub";
}
bool GameState::isGameActive() const 
{ 
    return false;
}

// Setters
void GameState::setPlayer(Trainer *p) 
{ 
    return;
}
void GameState::setCurrentGym(Gym *g) 
{ 
    return;
}
void GameState::setShop(Shop *s) 
{ 
    return;
}
void GameState::addBadge() 
{ 
    return;
}
void GameState::setPlayerName(const string &name) 
{ 
    return;
}
void GameState::setGameActive(bool active) 
{ 
    return;
}

// Save game
bool GameState::saveGame(const string &filename)
{
    return false;
}

// Load game
bool GameState::loadGame(const string &filename)
{
    return false;
}

// Reset game
void GameState::resetGame()
{
    return;
}