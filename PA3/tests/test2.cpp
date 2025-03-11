//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test2.cpp
#include <iostream>
#include <sstream>
#include "../include/Pokemon.hpp"
#include "../include/Move.hpp"
#include "../include/Armor.hpp"
#include "../include/Potion.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

void printTestResult(const string &testName, bool passed, double points, const string &debugInfo = "")
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
    double score = 0;
    cout << COLOR_BLUE << "=== Test 2: Testing Pokemon Class ===" << COLOR_RESET << endl;

    // --- Constructor and basic getters ---
    {
        cout << COLOR_YELLOW << "\n--- Pokemon Constructor and Getter Tests ---" << COLOR_RESET << endl;

        Pokemon pDefault;
        bool basicDefault = (pDefault.getName() == "Pikachu" &&
                             pDefault.getType() == "Electric" &&
                             pDefault.getMaxHP() == 100 &&
                             pDefault.getCurrentHP() == 100 &&
                             pDefault.getMoveCount() == 0 &&
                             !pDefault.isFainted());
        if (!basicDefault)
        {
            ostringstream debug;
            debug << "Default Pokemon: Expected [Pikachu,Electric,100,100,0,false] and got ["
                  << pDefault.getName() << "," << pDefault.getType() << ","
                  << pDefault.getMaxHP() << "," << pDefault.getCurrentHP() << ","
                  << pDefault.getMoveCount() << "," << pDefault.isFainted() << "]";
            printTestResult("Default Pokemon Constructor", basicDefault, 1, debug.str());
        }
        else
            printTestResult("Default Pokemon Constructor", basicDefault, 1);
        score += basicDefault ? 1 : 0;

        Pokemon pCustom("Bulbasaur", "Grass", 120);
        bool basicCustom = (pCustom.getName() == "Bulbasaur" &&
                            pCustom.getType() == "Grass" &&
                            pCustom.getMaxHP() == 120 &&
                            pCustom.getCurrentHP() == 120 &&
                            pCustom.getMoveCount() == 0 &&
                            !pCustom.isFainted());
        if (!basicCustom)
        {
            ostringstream debug;
            debug << "Custom Pokemon: Expected [Bulbasaur,Grass,120,120,0,false] and got ["
                  << pCustom.getName() << "," << pCustom.getType() << ","
                  << pCustom.getMaxHP() << "," << pCustom.getCurrentHP() << ","
                  << pCustom.getMoveCount() << "," << pCustom.isFainted() << "]";
            printTestResult("Custom Pokemon Constructor", basicCustom, 1, debug.str());
        }
        else
            printTestResult("Custom Pokemon Constructor", basicCustom, 1);
        score += basicCustom ? 1 : 0;

        // Copy constructor test
        Pokemon pCopy(pCustom);
        bool copyTest = (pCopy.getName() == "Bulbasaur" &&
                         pCopy.getCurrentHP() == 120);
        if (!copyTest)
        {
            ostringstream debug;
            debug << "Copy Constructor: Expected [Bulbasaur,120] and got ["
                  << pCopy.getName() << "," << pCopy.getCurrentHP() << "]";
            printTestResult("Pokemon Copy Constructor", copyTest, 1, debug.str());
        }
        else
            printTestResult("Pokemon Copy Constructor", copyTest, 1);
        score += copyTest ? 1 : 0;

        //Copy From Test
        Pokemon pAssign;
        pAssign.copyFrom(pCustom);
        bool copyFromTest = (pAssign.getName() == "Bulbasaur" &&
                             pAssign.getCurrentHP() == 120 &&
                             pAssign.getMoveCount() == pCustom.getMoveCount());
        if (!copyFromTest)
        {
            ostringstream debug;
            debug << "CopyFrom: Expected [Bulbasaur,120] and move count " << pCustom.getMoveCount()
                  << "; got [" << pAssign.getName() << "," << pAssign.getCurrentHP() 
                  << "] and move count " << pAssign.getMoveCount();
            printTestResult("Pokemon CopyFrom", copyFromTest, 3, debug.str());
        }
        else
            printTestResult("Pokemon CopyFrom", copyFromTest, 3);
        score += copyFromTest ? 3 : 0;
    }

    // --- Move management ---
    {
        cout << COLOR_YELLOW << "\n--- Pokemon Move Management Tests ---" << COLOR_RESET << endl;
        Pokemon p("Charizard", "Fire", 150);
        Move m1("Flamethrower", 90, 85, 15);
        Move m2("Dragon Claw", 80, 90, 20);

        bool add1 = p.addMove(m1);
        bool count1 = (p.getMoveCount() == 1);
        if (!(add1 && count1))
        {
            ostringstream debug;
            debug << "Add First Move: Expected move count 1, got " << p.getMoveCount();
            printTestResult("Add First Move", add1 && count1, 1, debug.str());
        }
        else
            printTestResult("Add First Move", add1 && count1, 1);
        score += (add1 && count1) ? 1 : 0;

        bool add2 = p.addMove(m2);
        bool count2 = (p.getMoveCount() == 2);
        if (!(add2 && count2))
        {
            ostringstream debug;
            debug << "Add Second Move: Expected move count 2, got " << p.getMoveCount();
            printTestResult("Add Second Move", add2 && count2, 1, debug.str());
        }
        else
            printTestResult("Add Second Move", add2 && count2, 1);
        score += (add2 && count2) ? 1 : 0;

        // Test dynamic expansion by adding extra moves
        Move m3("Fire Blast", 110, 70, 5);
        Move m4("Air Slash", 75, 95, 10);
        p.addMove(m3);
        p.addMove(m4);
        bool expansion = (p.getMoveCount() == 4);
        bool orderCorrect = (p.getMoveAtIndex(0)->getName() == "Flamethrower" &&
                             p.getMoveAtIndex(1)->getName() == "Dragon Claw" &&
                             p.getMoveAtIndex(2)->getName() == "Fire Blast" &&
                             p.getMoveAtIndex(3)->getName() == "Air Slash");
        if (!(expansion && orderCorrect))
        {
            ostringstream debug;
            debug << "Expected moves in order [Flamethrower, Dragon Claw, Fire Blast, Air Slash]. Got: ["
                  << p.getMoveAtIndex(0)->getName() << ", "
                  << p.getMoveAtIndex(1)->getName() << ", "
                  << p.getMoveAtIndex(2)->getName() << ", "
                  << p.getMoveAtIndex(3)->getName() << "]";
            printTestResult("Move Array Expansion", expansion && orderCorrect, 2, debug.str());
        }
        else
            printTestResult("Move Array Expansion", expansion && orderCorrect, 2);
        score += (expansion && orderCorrect) ? 2 : 0;

        // hasMove check
        bool hasIt = p.hasMove("Fire Blast") && !p.hasMove("Splash");
        if (!hasIt)
        {
            ostringstream debug;
            debug << "hasMove: Expected true for 'Fire Blast' and false for 'Splash'";
            printTestResult("Pokemon hasMove Check", hasIt, 1, debug.str());
        }
        else
            printTestResult("Pokemon hasMove Check", hasIt, 1);
        score += hasIt ? 1 : 0;

        // Remove move test and boundary condition
        bool removeOk = p.removeMove(1); // remove "Dragon Claw"
        bool afterRemove = (p.getMoveCount() == 3 &&
                            p.getMoveAtIndex(0)->getName() == "Flamethrower" &&
                            p.getMoveAtIndex(1)->getName() == "Fire Blast");
        bool removeFail = !p.removeMove(10); // invalid index removal should return false
        if (!(removeOk && afterRemove && removeFail))
        {
            ostringstream debug;
            debug << "After removal: Expected count=3 and order [Flamethrower,Fire Blast,...]. Got count "
                  << p.getMoveCount() << " with moves: ";
            for (int i = 0; i < p.getMoveCount(); i++)
                debug << p.getMoveAtIndex(i)->getName() << " ";
            printTestResult("Remove Move and Boundary Check", removeOk && afterRemove && removeFail, 2, debug.str());
        }
        else
            printTestResult("Remove Move and Boundary Check", removeOk && afterRemove && removeFail, 2);
        score += (removeOk && afterRemove && removeFail) ? 2 : 0;
    }

    // --- Battle functionality (damage, healing, fainting, reset) ---
    {
        cout << COLOR_YELLOW << "\n--- Pokemon Battle Functionality Tests ---" << COLOR_RESET << endl;
        Pokemon p("Arcanine", "Fire", 200);

        // Damage test
        p.takeDamage(50);
        bool damageTest = (p.getCurrentHP() == 150);
        if (!damageTest)
        {
            ostringstream debug;
            debug << "Take Damage: Expected HP 150, got " << p.getCurrentHP();
            printTestResult("Take Damage", damageTest, 1, debug.str());
        }
        else
            printTestResult("Take Damage", damageTest, 1);
        score += damageTest ? 1 : 0;

        // Healing test
        p.heal(30);
        bool healTest = (p.getCurrentHP() == 180);
        if (!healTest)
        {
            ostringstream debug;
            debug << "Healing: Expected HP 180, got " << p.getCurrentHP();
            printTestResult("Healing", healTest, 1, debug.str());
        }
        else
            printTestResult("Healing", healTest, 1);
        score += healTest ? 1 : 0;

        // Over-healing check
        p.heal(50);
        bool overHeal = (p.getCurrentHP() == 200);
        if (!overHeal)
        {
            ostringstream debug;
            debug << "Over-Healing: Expected capped HP 200, got " << p.getCurrentHP();
            printTestResult("Over-Healing (Cap at MaxHP)", overHeal, 1, debug.str());
        }
        else
            printTestResult("Over-Healing (Cap at MaxHP)", overHeal, 1);
        score += overHeal ? 1 : 0;

        // Fainting test
        p.takeDamage(220);
        bool faintTest = (p.isFainted() && p.getCurrentHP() == 0);
        if (!faintTest)
        {
            ostringstream debug;
            debug << "Fainting: Expected fainted with HP 0, got HP "
                  << p.getCurrentHP() << " and fainted flag " << p.isFainted();
            printTestResult("Pokemon Fainting", faintTest, 1, debug.str());
        }
        else
            printTestResult("Pokemon Fainting", faintTest, 1);
        score += faintTest ? 1 : 0;

        // Reset HP test
        p.resetHP();
        bool resetTest = (p.getCurrentHP() == p.getMaxHP() && !p.isFainted());
        if (!resetTest)
        {
            ostringstream debug;
            debug << "Reset HP: Expected currentHP " << p.getMaxHP() << " and not fainted, got HP "
                  << p.getCurrentHP() << " and fainted flag " << p.isFainted();
            printTestResult("Reset HP", resetTest, 1, debug.str());
        }
        else
            printTestResult("Reset HP", resetTest, 1);
        score += resetTest ? 1 : 0;
    }

    cout << COLOR_BLUE << "\nTest 2 Total Score: " << score << "/18 points" << COLOR_RESET << endl;
    return 0;
}