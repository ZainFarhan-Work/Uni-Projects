//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/GameState.cpp
#include "../include/GameState.hpp"
#include <iostream>

// Constructor
GameState::GameState(Trainer *p, Gym *g, Shop *s)
{
    player = p;
    currentGym = g;
    shop = s;

    playerName = p->getName();
    badges = 0;

}

// Destructor
GameState::~GameState()
{
    // We may or may not own these pointers. If we do, we delete them:
    // delete player;
    // delete currentGym;
    // delete shop;

    // if (player != nullptr)
    // {
    //     delete player;
    // }

    // if (currentGym != nullptr)
    // {
    //     delete currentGym;
    // }

    // if (shop != nullptr)
    // {
    //     delete currentGym;
    // }
    
}

// Getters
Trainer *GameState::getPlayer() const 
{ 
    return player;
}
Gym *GameState::getCurrentGym() const 
{ 
    return currentGym;
}
Shop *GameState::getShop() const 
{ 
    return shop;
}
int GameState::getBadges() const 
{ 
    return badges;
}
string GameState::getPlayerName() const 
{ 
    return player->getName();
}
bool GameState::isGameActive() const 
{ 
    return gameActive;
}

// Setters
void GameState::setPlayer(Trainer *p) 
{ 
    player = p;

    return;
}
void GameState::setCurrentGym(Gym *g) 
{
    currentGym = g;

    return;
}
void GameState::setShop(Shop *s) 
{
    shop = s;

    return;
}
void GameState::addBadge() 
{
    badges++;

    return;
}
void GameState::setPlayerName(const string &name) 
{
    playerName = name; 
    return;
}
void GameState::setGameActive(bool active) 
{
    gameActive = active; 
    return;
}

// Save game
bool GameState::saveGame(const string &filename)
{
    ofstream saveFile(filename);

    if (!saveFile)
    {
        cout << "Error Opening File." << endl;
        return false;
    }

    saveFile << playerName << endl;
    saveFile << badges << endl;
    saveFile << gameActive << endl;

    saveFile.close();

    return true;
}

// Load game
bool GameState::loadGame(const string &filename)
{
    ifstream loadFile(filename);

    if (!loadFile)
    {
        cout << "Error Opening File." << endl;
        return false;
    }

    loadFile >> playerName;
    loadFile >> badges;
    loadFile >> gameActive;

    loadFile.close();

    return true;
}

// Reset game
void GameState::resetGame()
{
    badges = 0;
    gameActive = false;

    return;
}