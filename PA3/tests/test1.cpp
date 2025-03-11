//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test1.cpp
#include <iostream>
#include <sstream>
#include "../include/Move.hpp"
#include "../include/Armor.hpp"
#include "../include/Potion.hpp"
using namespace std;

// Colors for test output
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
    cout << COLOR_BLUE << "=== Test 1: Testing Move, Armor and Potion Classes ===" << COLOR_RESET << endl;

    // --- Testing Move class ---
    {
        cout << COLOR_YELLOW << "\n--- Move Tests ---" << COLOR_RESET << endl;

        // Default constructor
        Move defaultMove;
        bool defaultCorrect = (defaultMove.getName() == "Tackle" &&
                               defaultMove.getPower() == 40 &&
                               defaultMove.getAccuracy() == 100 &&
                               defaultMove.getPP() == 35 &&
                               defaultMove.getMaxPP() == 35);
        if (!defaultCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Tackle,40,100,35,35] - Got: ["
                  << defaultMove.getName() << ","
                  << defaultMove.getPower() << ","
                  << defaultMove.getAccuracy() << ","
                  << defaultMove.getPP() << ","
                  << defaultMove.getMaxPP() << "]";
            printTestResult("Default Move Constructor & Getters", defaultCorrect, 1, debug.str());
        }
        else
            printTestResult("Default Move Constructor & Getters", defaultCorrect, 1);
        score += defaultCorrect ? 1 : 0;

        // Parameterized constructor
        Move customMove("Thunderbolt", 90, 85, 15);
        bool paramCorrect = (customMove.getName() == "Thunderbolt" &&
                             customMove.getPower() == 90 &&
                             customMove.getAccuracy() == 85 &&
                             customMove.getPP() == 15 &&
                             customMove.getMaxPP() == 15);
        if (!paramCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Thunderbolt,90,85,15,15] - Got: ["
                  << customMove.getName() << ","
                  << customMove.getPower() << ","
                  << customMove.getAccuracy() << ","
                  << customMove.getPP() << ","
                  << customMove.getMaxPP() << "]";
            printTestResult("Custom Move Constructor & Getters", paramCorrect, 1, debug.str());
        }
        else
            printTestResult("Custom Move Constructor & Getters", paramCorrect, 1);
        score += paramCorrect ? 1 : 0;

        // Copy constructor
        Move copyMove(customMove);
        bool copyCorrect = (copyMove.getName() == "Thunderbolt" &&
                            copyMove.getPower() == 90 &&
                            copyMove.getAccuracy() == 85 &&
                            copyMove.getPP() == 15);
        if (!copyCorrect)
        {
            ostringstream debug;
            debug << "Copy Constructor Error: Expected name Thunderbolt, power 90, accuracy 85, PP 15; Got: ["
                  << copyMove.getName() << ","
                  << copyMove.getPower() << ","
                  << copyMove.getAccuracy() << ","
                  << copyMove.getPP() << "]";
            printTestResult("Move Copy Constructor", copyCorrect, 1, debug.str());
        }
        else
            printTestResult("Move Copy Constructor", copyCorrect, 1);
        score += copyCorrect ? 1 : 0;

        // Use move: should decrement PP if available
        bool useOk = customMove.use();
        bool ppAfterUse = customMove.getPP() == 14;
        if (!(useOk && ppAfterUse))
        {
            ostringstream debug;
            debug << "After use: Expected PP 14, Got PP " << customMove.getPP();
            printTestResult("Move Usage and PP Decrement", useOk && ppAfterUse, 1, debug.str());
        }
        else
            printTestResult("Move Usage and PP Decrement", useOk && ppAfterUse, 1);
        score += (useOk && ppAfterUse) ? 1 : 0;

        // PP edge: using last PP and then no more usage
        Move lowPPMove("Last Resort", 100, 80, 1);
        bool usedLastPP = lowPPMove.use();
        bool noMorePP = !lowPPMove.use();
        bool outOfPP = lowPPMove.isOutOfPP();
        if (!(usedLastPP && noMorePP && outOfPP))
        {
            ostringstream debug;
            debug << "PP edge: Expected useLast true, second use false, isOutOfPP true; Got: useLast="
                  << usedLastPP << ", second use=" << !noMorePP << ", isOut=" << outOfPP;
            printTestResult("Move PP Edge Cases", usedLastPP && noMorePP && outOfPP, 1, debug.str());
        }
        else
            printTestResult("Move PP Edge Cases", usedLastPP && noMorePP && outOfPP, 1);
        score += (usedLastPP && noMorePP && outOfPP) ? 1 : 0;

        // Restore PP
        lowPPMove.restore();
        bool restored = (lowPPMove.getPP() == lowPPMove.getMaxPP() && !lowPPMove.isOutOfPP());
        if (!restored)
        {
            ostringstream debug;
            debug << "After restore: Expected PP=" << lowPPMove.getMaxPP() << " and not out; Got PP="
                  << lowPPMove.getPP() << ", isOut=" << lowPPMove.isOutOfPP();
            printTestResult("Move PP Restoration", restored, 1, debug.str());
        }
        else
            printTestResult("Move PP Restoration", restored, 1);
        score += restored ? 1 : 0;
    }

    // --- Testing Armor class ---
    {
        cout << COLOR_YELLOW << "\n--- Armor Tests ---" << COLOR_RESET << endl;

        // Default constructor
        Armor defaultArmor;
        bool defaultArmorCorrect = (defaultArmor.getName() == "Cloth" &&
                                    defaultArmor.getDefenseBonus() == 0 &&
                                    defaultArmor.getWeight() == 0.0);
        if (!defaultArmorCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Cloth, 0, 0.0] - Got: ["
                  << defaultArmor.getName() << ", "
                  << defaultArmor.getDefenseBonus() << ", "
                  << defaultArmor.getWeight() << "]";
            printTestResult("Default Armor Constructor", defaultArmorCorrect, 1, debug.str());
        }
        else
            printTestResult("Default Armor Constructor", defaultArmorCorrect, 1);
        score += defaultArmorCorrect ? 1 : 0;

        // Parameterized constructor
        Armor customArmor("Steel Plate", 20, 15.5);
        bool customArmorCorrect = (customArmor.getName() == "Steel Plate" &&
                                   customArmor.getDefenseBonus() == 20 &&
                                   customArmor.getWeight() == 15.5);
        if (!customArmorCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Steel Plate, 20, 15.5] - Got: ["
                  << customArmor.getName() << ", "
                  << customArmor.getDefenseBonus() << ", "
                  << customArmor.getWeight() << "]";
            printTestResult("Custom Armor Constructor", customArmorCorrect, 1, debug.str());
        }
        else
            printTestResult("Custom Armor Constructor", customArmorCorrect, 1);
        score += customArmorCorrect ? 1 : 0;

        // Copy constructor
        Armor copyArmor(customArmor);
        bool copyArmorCorrect = (copyArmor.getName() == "Steel Plate" &&
                                 copyArmor.getDefenseBonus() == 20 &&
                                 copyArmor.getWeight() == 15.5);
        if (!copyArmorCorrect)
        {
            ostringstream debug;
            debug << "Copy Error: Expected: [Steel Plate, 20, 15.5] - Got: ["
                  << copyArmor.getName() << ", "
                  << copyArmor.getDefenseBonus() << ", "
                  << copyArmor.getWeight() << "]";
            printTestResult("Armor Copy Constructor", copyArmorCorrect, 1, debug.str());
        }
        else
            printTestResult("Armor Copy Constructor", copyArmorCorrect, 1);
        score += copyArmorCorrect ? 1 : 0;

        // isHeavy function (heavy if weight > 10)
        bool heavyCheck = (customArmor.isHeavy() && !defaultArmor.isHeavy());
        if (!heavyCheck)
        {
            ostringstream debug;
            debug << "Expected: Steel Plate is heavy and Cloth is not. Got: isHeavy(Steel Plate)="
                  << customArmor.isHeavy() << ", isHeavy(Cloth)=" << defaultArmor.isHeavy();
            printTestResult("Heavy Armor Check", heavyCheck, 1, debug.str());
        }
        else
            printTestResult("Heavy Armor Check", heavyCheck, 1);
        score += heavyCheck ? 1 : 0;
    }

    // --- Testing Potion class ---
    {
        cout << COLOR_YELLOW << "\n--- Potion Tests ---" << COLOR_RESET << endl;

        // Default constructor
        Potion defaultPotion;
        bool defaultPotionCorrect = (defaultPotion.getName() == "Basic Potion" &&
                                     defaultPotion.getHealAmount() == 20 &&
                                     defaultPotion.getCost() == 10 &&
                                     defaultPotion.canUse());
        if (!defaultPotionCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Basic Potion, 20, 10, true] - Got: ["
                  << defaultPotion.getName() << ", "
                  << defaultPotion.getHealAmount() << ", "
                  << defaultPotion.getCost() << ", "
                  << defaultPotion.canUse() << "]";
            printTestResult("Default Potion Constructor", defaultPotionCorrect, 0.5, debug.str());
        }
        else
            printTestResult("Default Potion Constructor", defaultPotionCorrect, 0.5);
        score += defaultPotionCorrect ? 0.5 : 0;

        // Parameterized constructor
        Potion customPotion("Super Potion", 50, 30);
        bool customPotionCorrect = (customPotion.getName() == "Super Potion" &&
                                    customPotion.getHealAmount() == 50 &&
                                    customPotion.getCost() == 30 &&
                                    customPotion.canUse());
        if (!customPotionCorrect)
        {
            ostringstream debug;
            debug << "Expected: [Super Potion, 50, 30, true] - Got: ["
                  << customPotion.getName() << ", "
                  << customPotion.getHealAmount() << ", "
                  << customPotion.getCost() << ", "
                  << customPotion.canUse() << "]";
            printTestResult("Custom Potion Constructor", customPotionCorrect, 0.5, debug.str());
        }
        else
            printTestResult("Custom Potion Constructor", customPotionCorrect, 0.5);
        score += customPotionCorrect ? 0.5 : 0;

        // Copy constructor
        Potion copyPotion(customPotion);
        bool copyPotionCorrect = (copyPotion.getName() == "Super Potion" &&
                                  copyPotion.getHealAmount() == 50 &&
                                  copyPotion.getCost() == 30 &&
                                  copyPotion.canUse());
        if (!copyPotionCorrect)
        {
            ostringstream debug;
            debug << "Copy Error: Expected: [Super Potion, 50, 30, true] - Got: ["
                  << copyPotion.getName() << ", "
                  << copyPotion.getHealAmount() << ", "
                  << copyPotion.getCost() << ", "
                  << copyPotion.canUse() << "]";
            printTestResult("Potion Copy Constructor", copyPotionCorrect, 0.5, debug.str());
        }
        else
            printTestResult("Potion Copy Constructor", copyPotionCorrect, 0.5);
        score += copyPotionCorrect ? 0.5 : 0;

        // Use potion: after use cannot be used again
        customPotion.use();
        bool usedPotion = (!customPotion.canUse() && customPotion.getIsUsed());
        if (!usedPotion)
        {
            ostringstream debug;
            debug << "Usage Error: After use, expected canUse=false and isUsed=true, Got: canUse="
                  << customPotion.canUse() << ", isUsed=" << customPotion.getIsUsed();
            printTestResult("Potion Usage and Status", usedPotion, 0.5, debug.str());
        }
        else
            printTestResult("Potion Usage and Status", usedPotion, 0.5);
        score += usedPotion ? 0.5 : 0;
    }

    cout << COLOR_BLUE << "\nTest 1 Total Score: " << score << "/12 points" << COLOR_RESET << endl;
    return 0;
}