//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test6.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/GameState.hpp"
#include "../include/Trainer.hpp"
#include "../include/Gym.hpp"
#include "../include/Shop.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

void printTestResult(const string &testName, bool passed, int points, const string &debugInfo = "")
{
    if (passed)
        cout << COLOR_GREEN << "[PASSED] " << testName << " (" << points << " points)" << COLOR_RESET << endl;
    else
    {
        cout << COLOR_RED << "[FAILED] " << testName << " (0 points)" << COLOR_RESET << endl;
        if (!debugInfo.empty())
            cout << COLOR_YELLOW << "       Debug: " << debugInfo << COLOR_RESET << endl;
    }
}

int main()
{
    int score = 0;
    cout << COLOR_BLUE << "=== Test 6: Testing GameState Class ===" << COLOR_RESET << endl;

    // Setup game state components
    Trainer *player = new Trainer("Red");
    Gym *gym = new Gym(player, "Thunder Badge", 3);
    Shop *shop = new Shop();

    GameState gs(player, gym, shop);
    gs.setPlayerName("Red");
    gs.addBadge();
    gs.setGameActive(true);

    // Check initial game state.
    bool stateCheck = (gs.getPlayer()->getName() == "Red" &&
                       gs.getCurrentGym()->getBadgeName() == "Thunder Badge" &&
                       gs.getBadges() == 1 &&
                       gs.getPlayerName() == "Red" &&
                       gs.isGameActive());
    {
        ostringstream debug;
        if (!stateCheck)
        {
            debug << "Expected: Player=Red, Badge='Thunder Badge', Badges=1, Active=true; "
                  << "Got: Player=" << gs.getPlayer()->getName()
                  << ", Badge=" << gs.getCurrentGym()->getBadgeName()
                  << ", Badges=" << gs.getBadges()
                  << ", PlayerName=" << gs.getPlayerName()
                  << ", isActive=" << gs.isGameActive();
        }
        printTestResult("Initial GameState Setup", stateCheck, 5, debug.str());
    }
    score += stateCheck ? 5 : 0;

    // Test saving game state
    bool saveOk = gs.saveGame("gamestate_test.txt");
    // Now reset game state and load saved state.
    gs.resetGame();
    bool resetOk = (!gs.isGameActive() && gs.getBadges() == 0);
    bool loadOk = gs.loadGame("gamestate_test.txt");
    bool loadCheck = (gs.getPlayerName() == "Red" && gs.getBadges() == 1);
    {
        ostringstream debug;
        if (!saveOk)
            debug << "saveGame() returned false; ";
        if (!resetOk)
            debug << "After reset, expected game not active and badges 0, got isActive=" << gs.isGameActive()
                  << " and badges=" << gs.getBadges() << "; ";
        if (!loadOk)
            debug << "loadGame() returned false; ";
        if (!loadCheck)
            debug << "After load, expected PlayerName=Red and badges=1, got PlayerName="
                  << gs.getPlayerName() << " and badges=" << gs.getBadges();
        printTestResult("Save, Reset & Load GameState", (saveOk && resetOk && loadOk && loadCheck), 8, debug.str());
    }
    score += (saveOk && resetOk && loadOk && loadCheck) ? 8 : 0;

    // Clean up file
    remove("gamestate_test.txt");
    cout << COLOR_BLUE << "\nTest 6 Total Score: " << score << "/13 points" << COLOR_RESET << endl;

    delete player;
    delete gym;
    delete shop;
    return 0;
}