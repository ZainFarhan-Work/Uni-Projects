/// filepath: /f:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test4.cpp
#include <iostream>
#include <sstream>
#include "../include/Shop.hpp"
#include "../include/Trainer.hpp"
#include "../include/Potion.hpp"
#include "../include/Armor.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

// printTestResult now accepts an optional debugInfo string.
void printTestResult(const string& testName, bool passed, int points, const string &debugInfo = "") {
    if(passed)
        cout << COLOR_GREEN << "[PASSED] " << testName << " (" << points << " points)" << COLOR_RESET << endl;
    else {
        cout << COLOR_RED << "[FAILED] " << testName << " (0 points)" << COLOR_RESET << endl;
        if (!debugInfo.empty())
            cout << COLOR_YELLOW << "       Debug: " << debugInfo << COLOR_RESET << endl;
    }
}

int main(){
    int score = 0;
    cout << COLOR_BLUE << "=== Test 4: Testing Shop Class ===" << COLOR_RESET << endl;
    
    Shop shop;
    // --- Test adding items ---
    {
        Potion pot1("Basic Potion", 20, 10);
        Potion pot2("Super Potion", 50, 30);
        shop.addPotion(pot1);
        shop.addPotion(pot2);
        bool countOk = (shop.getPotionCount() == 2);
        {
            ostringstream debug;
            if (!countOk)
                debug << "Expected potion count 2, got " << shop.getPotionCount();
            printTestResult("Add Potions & Count", countOk, 3, debug.str());
        }
        score += countOk ? 3 : 0;
        
        Armor arm1("Leather", 5, 5.0);
        Armor arm2("Chainmail", 15, 12.0);
        shop.addArmor(arm1);
        shop.addArmor(arm2);
        bool armorCount = (shop.getArmorCount() == 2);
        {
            ostringstream debug;
            if (!armorCount)
                debug << "Expected armor count 2, got " << shop.getArmorCount();
            printTestResult("Add Armors & Count", armorCount, 3, debug.str());
        }
        score += armorCount ? 3 : 0;
    }
    
    // --- Test selling items (valid and error cases) ---
    {
        Trainer t("SalesTest");
        t.addMoney(200);
        // Sell a potion successfully.
        bool sellPot = shop.sellPotionTo(0, t);
        bool trainerPotionAdded = (t.getPotionCount() == 1);
        {
            ostringstream debug;
            if (!sellPot)
                debug << "sellPotionTo returned false; ";
            if (!trainerPotionAdded)
                debug << "Trainer potion count expected 1, got " << t.getPotionCount();
            printTestResult("Sell Potion Successful", sellPot && trainerPotionAdded, 3, debug.str());
        }
        score += (sellPot && trainerPotionAdded) ? 3 : 0;
        
        // Trying to sell with wrong index.
        bool sellFail = !shop.sellPotionTo(10, t);
        {
            ostringstream debug;
            if (!sellFail)
                debug << "sellPotionTo with invalid index did not fail as expected.";
            printTestResult("Sell Potion Invalid Index", sellFail, 2, debug.str());
        }
        score += sellFail ? 2 : 0;
        
        // Test selling armor: assume armor sold equips a specific Pokemon from trainer.
        Pokemon* p = new Pokemon("Golem", "Rock", 120);
        t.addPokemon(p);
        bool sellArmor = shop.sellArmorTo(0, t, 0); // sell first armor to equip to first Pokemon
        bool armorEquipped = (t.getPokemonAtIndex(0)->getEquippedArmor() != nullptr);
        {
            ostringstream debug;
            if (!sellArmor)
                debug << "sellArmorTo returned false; ";
            if (!armorEquipped)
                debug << "Expected Pokemon to have equipped an armor, but got nullptr.";
            printTestResult("Sell Armor and Equip", sellArmor && armorEquipped, 3, debug.str());
        }
        score += (sellArmor && armorEquipped) ? 3 : 0;
        
        delete p;
    }
    
    cout << COLOR_BLUE << "\nTest 4 Total Score: " << score << "/14 points" << COLOR_RESET << endl;
    return 0;
}