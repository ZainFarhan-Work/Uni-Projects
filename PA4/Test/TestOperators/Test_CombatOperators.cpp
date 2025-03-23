#include <iostream>
#include <sstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip>
#include <cstdlib>
#include "../../ACS_61.cpp"

using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW  "\033[33m"

void testWeaponPostIncrementOperator(int &marks)
{
    int tempmarks = 0;
    int temptotal = 3;

    CombatAircraft ca1("", 100, 100, AircraftStatus::OnGround, "Missiles", 7, 25);
    CombatAircraft ca2(ca1++);
    if (ca2.getWeaponCount() == 7 && ca2.getWeaponStrength() == 25 && ca1.getWeaponCount() == 8 && ca1.getWeaponStrength() == 25)
    {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc1("", 100, 100, AircraftStatus::OnGround, "Stones", 100, 1, false, 3);
    GuardianCraft gc2(gc1++);
    if (gc2.getWeaponCount() == 100 && gc2.getWeaponStrength() == 1 && gc1.getWeaponCount() == 101 && gc1.getWeaponStrength() == 1)
    {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    CombatAircraft ca3("", 100, 100, AircraftStatus::Airborne, "Rockets", 3, 50);
    CombatAircraft ca4(ca3++);
    if (ca4.getWeaponCount() == 3 && ca4.getWeaponStrength() == 50 && ca3.getWeaponCount() == 3 && ca3.getWeaponStrength() == 50)
    {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Weapon Post-Increment Operator ++ : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testWeaponPreDecrementOperator(int &marks)
{
    int tempmarks = 0;
    int temptotal = 3;

    CombatAircraft ca1("", 100, 100, AircraftStatus::OnGround, "Missiles", 7, 25);
    CombatAircraft ca2(--ca1);
    if (ca2.getWeaponCount() == 6 && ca2.getWeaponStrength() == 25 && ca1.getWeaponCount() == 6 && ca1.getWeaponStrength() == 25)
    {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc1("", 100, 100, AircraftStatus::OnGround, "Stones", 100, 1, false, 3);
    GuardianCraft gc2(--gc1);
    if (gc2.getWeaponCount() == 99 && gc2.getWeaponStrength() == 1 && gc1.getWeaponCount() == 99 && gc1.getWeaponStrength() == 1)
    {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    CombatAircraft ca3("", 100, 100, AircraftStatus::OnGround, "Rockets", 5, 50);
    --ca3;
    --ca3;
    --ca3;
    --ca3;
    --ca3;
    --ca3;
    CombatAircraft ca4(--ca3);
    if (ca4.getWeaponCount() == 0 && ca4.getWeaponStrength() == 50 && ca3.getWeaponCount() == 0 && ca3.getWeaponStrength() == 50)
    {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Weapon Pre-Decrement Operator -- : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testOutputStreamOperator(int &marks)
{
    int tempmarks = 0;
    int temptotal = 3;

    CombatAircraft ca1("COMBAT1", 33, 64, AircraftStatus::OnGround, "Exploding Balloons", 5, 60);
    string expectedOutput1 = "Identifier: COMBAT1\n"
                             "Fuel Level: 33%\n"
                             "Health: 64%\n"
                             "Current Status: On Ground\n"
                             "Weapon Type: Exploding Balloons\n"
                             "Weapon Count: 5\n"
                             "Weapon Strength: 60\n";
    stringstream buffer;
    streambuf *oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ca1;
    string actualOutput1 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if (actualOutput1 == expectedOutput1)
    {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    CombatAircraft ca2("FighterJet", 22, 30, AircraftStatus::Airborne, "Missiles", 2, 50);
    string expectedOutput2 = "Identifier: FighterJet\n"
                             "Fuel Level: 22%\n"
                             "Health: 30%\n"
                             "Current Status: Airborne\n"
                             "Weapon Type: Missiles\n"
                             "Weapon Count: 2\n"
                             "Weapon Strength: 50\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ca2;
    string actualOutput2 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if (actualOutput2 == expectedOutput2)
    {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    CombatAircraft ca3("NoLongerCombatWorthy", 49, 0, AircraftStatus::Crashed, "Missiles", 1, 50);
    string expectedOutput3 = "Identifier: NoLongerCombatWorthy\n"
                             "Fuel Level: 49%\n"
                             "Health: 0%\n"
                             "Current Status: Crashed\n"
                             "Weapon Type: Missiles\n"
                             "Weapon Count: 1\n"
                             "Weapon Strength: 50\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ca3;
    string actualOutput3 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if (actualOutput3 == expectedOutput3)
    {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    marks += tempmarks;
    cout << YELLOW << "Output Stream Operator << : " << tempmarks << "/" << temptotal << endl << RESET;
}

int main()
{
    int marks = 0;
    const int TOTAL_MARKS = 9;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting CombatAircraft Operator Overloading Tests..." << RESET << endl << endl;

    testWeaponPostIncrementOperator(marks);
    cout << endl;
    testWeaponPreDecrementOperator(marks);
    cout << endl;
    testOutputStreamOperator(marks);
    cout << endl;

    if (marks == TOTAL_MARKS)
    {
        cout << GREEN << "CombatAircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    else
    {
        cout << RED << "CombatAircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    cout << "----------------------------------\n";
}