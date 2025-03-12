//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test3.cpp
#include <iostream>
#include <sstream>
#include "../include/Trainer.hpp"
#include "../include/Pokemon.hpp"
#include "../include/Potion.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// Added an optional debugInfo parameter
void printTestResult(const string &testName, bool passed, double points, const string &debugInfo = "") {
    if (passed)
        cout << COLOR_GREEN << "[PASSED] " << testName << " (" << points << " points)" << COLOR_RESET << endl;
    else {
        cout << COLOR_RED << "[FAILED] " << testName << " (0 points)" << COLOR_RESET << endl;
        if (!debugInfo.empty())
            cout << COLOR_YELLOW << "       Debug: " << debugInfo << COLOR_RESET << endl;
    }
}

int main(){
    double score = 0;
    cout << COLOR_BLUE << "=== Test 3: Testing Trainer Class ===" << COLOR_RESET << endl;
    
    // --- Trainer constructor and getters ---
    {
        Trainer t("Gary");
        bool nameCheck = (t.getName() == "Gary");
        bool partyInit = (t.getPartyCount() == 0);
        bool potionInit = (t.getPotionCount() == 0);
        bool moneyInit = (t.getMoney() == 0);
        bool overall = (nameCheck && partyInit && potionInit && moneyInit);
        ostringstream debug;
        if (!overall) {
            debug << "Expected: Name=Gary, Party=0, Potion=0, Money=0; Got: Name=" 
                  << t.getName() << ", Party=" << t.getPartyCount() 
                  << ", Potion=" << t.getPotionCount() 
                  << ", Money=" << t.getMoney();
        }
        printTestResult("Trainer Construction & Getters", overall, 3, debug.str());
        score += overall ? 3 : 0;
    }
    
    // --- Adding Pokemon and Potions ---
    {
        Trainer t("Ash");
        Pokemon* p1 = new Pokemon("Pikachu", "Electric", 100);
        Pokemon* p2 = new Pokemon("Charmander", "Fire", 90);
        cout << "Here\n";
        bool addP1 = t.addPokemon(p1);
        bool addP2 = t.addPokemon(p2);
        bool partyCountOk = (t.getPartyCount() == 2);
        {
            ostringstream debug;
            if (!(addP1 && addP2))
                debug << "addPokemon returned: " << addP1 << " and " << addP2;
            else if (!partyCountOk)
                debug << "Expected party count 2, got " << t.getPartyCount();
            printTestResult("Add Pokemon and Party Count", addP1 && addP2 && partyCountOk, 3, debug.str());
        }
        score += (addP1 && addP2 && partyCountOk) ? 3 : 0;
        
        Potion pot("Super Potion", 50, 30);
        bool addPot = t.addPotion(pot);
        bool potionCountOk = (t.getPotionCount() == 1);
        {
            ostringstream debug;
            if (!addPot)
                debug << "addPotion returned false.";
            else if (!potionCountOk)
                debug << "Expected potion count 1, got " << t.getPotionCount();
            printTestResult("Add Potion and Potion Count", addPot && potionCountOk, 3, debug.str());
        }
        score += (addPot && potionCountOk) ? 3 : 0;
        
        // Test using a potion on a Pokemon
        bool usePot = t.usePotion(0, 0); // Use first potion on first Pokemon
        bool potionUsed = !t.getPotionAtIndex(0)->canUse();
        {
            ostringstream debug;
            if (!usePot)
                debug << "usePotion returned false.";
            else if (!potionUsed)
                debug << "Expected potion to be used (canUse false), got canUse=" 
                      << t.getPotionAtIndex(0)->canUse();
            printTestResult("Use Potion on Pokemon", usePot && potionUsed, 3, debug.str());
        }
        score += (usePot && potionUsed) ? 3 : 0;
        
        // Test removing Pokemon (invalid index, then valid removal)
        bool removeFail = !t.removePokemon(10);
        bool removeOk = t.removePokemon(1); // remove Charmander
        bool newCount = (t.getPartyCount() == 1);
        {
            ostringstream debug;
            if (!removeFail)
                debug << "Removing at invalid index did not fail as expected; ";
            if (!removeOk)
                debug << "Valid removal (index 1) did not succeed; ";
            if (!newCount)
                debug << "Expected party count 1 after removal, got " << t.getPartyCount();
            printTestResult("Remove Pokemon and Boundary", removeFail && removeOk && newCount, 3, debug.str());
        }
        score += (removeFail && removeOk && newCount) ? 3 : 0;
        
        // Clean up: since Trainer does not delete Pokemon, delete manually.
        delete p2;  // Already removed
        delete p1;
    }

    // --- Money management ---
    {
        Trainer t("Brock");
        t.addMoney(100);
        bool enough = t.spendMoney(30);
        bool notEnough = !t.spendMoney(100);
        bool moneyOk = (t.getMoney() == 70);
        {
            ostringstream debug;
            if (!enough)
                debug << "spendMoney(30) failed; ";
            if (!notEnough)
                debug << "spendMoney(100) should fail with insufficient funds; ";
            if (!moneyOk)
                debug << "Expected money 70, got " << t.getMoney();
            printTestResult("Money management", enough && notEnough && moneyOk, 2, debug.str());
        }
        score += (enough && notEnough && moneyOk) ? 2 : 0;
    }

    
    // Test copy constructor and assignment operator for deep copy
    {
        Trainer t1("Misty");
        Pokemon* s = new Pokemon("Staryu", "Water", 80);
        t1.addPokemon(s);
        t1.addMoney(50);
        
        // Test copy constructor: create t2 from t1
        Trainer t2(t1);
        bool copyOk = (t2.getName() == "Misty" && t2.getPartyCount() == 1 && t2.getMoney() == 50);
        
        // Test assignment operator via copyFrom: copy t1 into t3
        Trainer t3;
        t3.copyFrom(t1);
        bool assignOk = (t3.getName() == "Misty" && t3.getPartyCount() == 1 && t3.getMoney() == 50);
        
        // Optionally modify t1 for deep-copy testing; t2 and t3 should remain unchanged.
        t1.removePokemon(0);
        t1.addMoney(100);
        bool deepCopyOk = (t2.getPartyCount() == 1 && t2.getMoney() == 50 &&
                           t3.getPartyCount() == 1 && t3.getMoney() == 50);
        
        {
            ostringstream debug;
            if (!copyOk)
            debug << "Copy constructor: Expected [Misty, party count 1, money 50]; Got ["
                  << t2.getName() << ", " << t2.getPartyCount() << ", " << t2.getMoney() << "]; ";
            if (!assignOk)
                debug << "Assignment operator: Expected [Misty, party count 1, money 50]; Got ["
                    << t3.getName() << ", " << t3.getPartyCount() << ", " << t3.getMoney() << "]; ";
            if (!deepCopyOk)
                debug << "After modifying original, expected copies unchanged; ";
            printTestResult("Trainer Copy & Assignment", copyOk && assignOk && deepCopyOk, 3, debug.str());
        }
        score += (copyOk && assignOk) ? 3 : 0;
        delete s;
    }
    
    cout << COLOR_BLUE << "\nTest 3 Total Score: " << score << "/20 points" << COLOR_RESET << endl;
    return 0;
}