#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <fstream>
#include "Trainer.hpp"
#include "Gym.hpp"
#include "Shop.hpp"
using namespace std;

class GameState
{
private:
    Trainer *player;
    Gym *currentGym;
    Shop *shop;
    int badges;
    string playerName;
    bool gameActive;

public:
    // Constructor and destructor
    GameState(Trainer *p = nullptr, Gym *g = nullptr, Shop *s = nullptr);
    ~GameState();

    // No copy constructor or assignment - game state is unique

    // Getters
    Trainer *getPlayer() const;
    Gym *getCurrentGym() const;
    Shop *getShop() const;
    int getBadges() const;
    string getPlayerName() const;
    bool isGameActive() const;

    // Setters
    void setPlayer(Trainer *p);
    void setCurrentGym(Gym *g);
    void setShop(Shop *s);
    void addBadge();
    void setPlayerName(const string &name);
    void setGameActive(bool active);

    // Game state management
    bool saveGame(const string &filename);
    bool loadGame(const string &filename);
    void resetGame();
};

#endif