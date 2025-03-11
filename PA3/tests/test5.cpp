#include <iostream>
#include <sstream>
#include "../include/Gym.hpp"
#include "../include/Trainer.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Battle.hpp"
#include "../include/Armor.hpp"
#include "../include/BattleHistory.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// Updated printTestResult accepts an optional debugInfo parameter.
void printTestResult(const string &testName, bool passed, int points, const string &debugInfo = "")
{
    if (passed)
        cout << COLOR_GREEN << "[PASSED] " << testName << " (" << points << " points)"
             << COLOR_RESET << endl;
    else
    {
        cout << COLOR_RED << "[FAILED] " << testName << " (0 points)"
             << COLOR_RESET << endl;
        if (!debugInfo.empty())
            cout << COLOR_YELLOW << "       Debug: " << debugInfo
                 << COLOR_RESET << endl;
    }
}

int main()
{
    int score = 0;
    cout << COLOR_BLUE << "=== Test 5: Testing Gym Class ===" << COLOR_RESET << endl;

    // Ensure deterministic mode is on
    Battle::deterministic = true;

    // Setup Leader and Gym Pokemon
    Trainer *leader = new Trainer("Brock");
    // Add two gym Pokemon with LOWER HP
    Pokemon *p1 = new Pokemon("Onix", "Rock", 50);  
    Pokemon *p2 = new Pokemon("Geodude", "Rock", 40);  
    
    // Give them weaker moves
    Move weakMove("Tackle", 20, 100, 10);
    p1->addMove(weakMove);
    p2->addMove(weakMove);
    
    leader->addPokemon(p1);
    leader->addPokemon(p2);

    Gym gym(leader, "Rock Badge", 2);
    gym.addGymPokemon(p1);
    gym.addGymPokemon(p2);

    // Create challenger with two Pokemon with HIGHER HP
    Trainer *challenger = new Trainer("Gary");
    Pokemon *cp1 = new Pokemon("Eevee", "Normal", 200);  
    Pokemon *cp2 = new Pokemon("Pikachu", "Electric", 200); 
    
    // Give them stronger moves
    Move strongMove("Hyper Beam", 60, 100, 10);  // Higher power move
    cp1->addMove(strongMove);
    cp2->addMove(strongMove);
    
    challenger->addPokemon(cp1);
    challenger->addPokemon(cp2);

    // --- Gym Battle Simulation ---
    bool battleResult = gym.battle(challenger);
    {
        ostringstream debug;
        if (!battleResult)
            debug << "Expected challenger to win the gym battle simulation, but battleResult was false.";
        printTestResult("Gym Battle Simulation", battleResult, 10, debug.str());
    }
    score += battleResult ? 10 : 0;

    // --- Gym Management: Removing a Gym Pokemon ---
    {
        bool removeFail = !gym.removeGymPokemon(10); // invalid index removal should fail
        bool removeOk = gym.removeGymPokemon(1);     // valid removal
        bool countOk = (gym.getPokemonCount() == 1);
        ostringstream debug;
        if (!removeFail)
            debug << "Expected removal at invalid index to fail; ";
        if (!removeOk)
            debug << "Expected removal at index 1 to succeed; ";
        if (!countOk)
            debug << "Expected gym party count 1 after removal, got " << gym.getPokemonCount() << "; ";
        printTestResult("Remove Gym Pokemon and Count Check", removeFail && removeOk && countOk, 5, debug.str());
        score += (removeFail && removeOk && countOk) ? 5 : 0;
    }

    // --- Gym Management: Heal All Gym Pokemon ---
    {
        // Create new Pokémon for the healing test
        Pokemon *testP1 = new Pokemon("Onix", "Rock", 50);
        Pokemon *testP2 = new Pokemon("Geodude", "Rock", 40);

        // Add them to the gym
        gym.addGymPokemon(testP1);
        gym.addGymPokemon(testP2);

        // Damage the Pokémon to ensure they need healing
        testP1->takeDamage(20); // Reduce HP to 30
        testP2->takeDamage(10); // Reduce HP to 30

        // Verify that the Pokémon's HP has been reduced
        bool damagedP1 = (testP1->getCurrentHP() == 30);
        bool damagedP2 = (testP2->getCurrentHP() == 30);

        ostringstream debug;
        if (!damagedP1)
            debug << "Expected " << testP1->getName() << " to have 30 HP after taking damage, but got " << testP1->getCurrentHP() << " HP. ";
        if (!damagedP2)
            debug << "Expected " << testP2->getName() << " to have 30 HP after taking damage, but got " << testP2->getCurrentHP() << " HP. ";

        // Heal all Pokémon in the gym
        gym.healAllPokemon();

        // Check if all Pokémon are healed
        bool healedP1 = (testP1->getCurrentHP() == testP1->getMaxHP());
        bool healedP2 = (testP2->getCurrentHP() == testP2->getMaxHP());

        if (!healedP1)
            debug << "After healing, expected " << testP1->getMaxHP()
                << " HP for " << testP1->getName() << ", but got " << testP1->getCurrentHP() << " HP. ";
        if (!healedP2)
            debug << "After healing, expected " << testP2->getMaxHP()
                << " HP for " << testP2->getName() << ", but got " << testP2->getCurrentHP() << " HP. ";

        bool healed = healedP1 && healedP2;
        printTestResult("Heal All Gym Pokemon", damagedP1 && damagedP2 && healed, 3, debug.str());
        score += (damagedP1 && damagedP2 && healed) ? 3 : 0;

        // Clean up
        delete testP1;
        delete testP2;
    }

    cout << COLOR_BLUE << "\nTest 5 Total Score: " << score << "/18 points" << COLOR_RESET << endl;

    // Clean up (if Gym does not delete pointers, free them here)
    delete challenger;
    delete leader;
    return 0;
}