#include <iostream>
#include <sstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip> 
#include <cstdlib>
#include "../../ACS_61.cpp"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"


void testEngagementCriteriaOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 8;

    GuardianCraft gc1("", 100, 100, AircraftStatus::Airborne, "Missiles", 5, 50, true, 0);
    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, false, 0, 50);
    if(gc1 *= ac1) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc2("", 100, 100, AircraftStatus::Airborne, "Missiles", 4, 50, true, 0);
    AbductorCraft ac2("", 100, 100, AircraftStatus::Crashed, false, 0, 10);
    if(!(gc2 *= ac2)) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    GuardianCraft gc3("", 100, 100, AircraftStatus::Airborne, "Missiles", 0, 0, true, 0);
    AbductorCraft ac3("", 100, 100, AircraftStatus::Airborne, false, 0, 2);
    if(!(gc3 *= ac3)) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    GuardianCraft gc4("", 100, 100, AircraftStatus::Airborne, "Missiles", 4, 4, true, 0);
    AbductorCraft ac4("", 100, 100, AircraftStatus::Airborne, true, 0, 50);
    if (!(gc4 *= ac4)) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    GuardianCraft gc5("", 100, 100, AircraftStatus::Airborne, "Missiles", 4, 4, true, 0);
    AbductorCraft ac5("", 100, 100, AircraftStatus::Airborne, false, 49, 50);
    if (!(gc5 *= ac5)) {
        tempmarks += 1;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    GuardianCraft gc6("", 100, 100, AircraftStatus::Airborne, "Missiles", 1, 10, false, 100);
    AbductorCraft ac6("", 100, 100, AircraftStatus::Airborne, false, 0, 0);
    if(gc6 *= ac6) {
        tempmarks += 2;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Engagement Criteria Operator *= : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testEngagementOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 8;

    GuardianCraft gc1("", 100, 100, AircraftStatus::Airborne, "Missiles", 5, 50, false, 1);
    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, false, 0, 10);
    gc1 * ac1;
    if(gc1.getWeaponCount() == 4 && gc1.getKillCount() == 1 && ac1.getHealth() == 50 && ac1.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc2("", 56, 49, AircraftStatus::Airborne, "Missiles", 4, 50, true, 0);
    AbductorCraft ac2("", 83, 42, AircraftStatus::Airborne, false, 0, 10);
    gc2 * ac2;
    if(gc2.getWeaponCount() == 3 && gc2.getKillCount() == 1 && ac2.getHealth() == 0 && ac2.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    GuardianCraft gc3("", 56, 49, AircraftStatus::Airborne, "Guns", 100, 2, true, 0);
    AbductorCraft ac3("", 83, 42, AircraftStatus::Airborne, true, 0, 10);
    gc3 * ac3;
    if(gc3.getWeaponCount() == 100 && gc3.getKillCount() == 0 && ac3.getHealth() == 42 && ac3.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    GuardianCraft gc4("", 59, 51, AircraftStatus::Airborne, "Guns", 82, 23, true, 4);
    AbductorCraft ac4("", 83, 0, AircraftStatus::Crashed, false, 0, 10);
    gc4 * ac4;
    if(gc4.getWeaponCount() == 82 && gc4.getKillCount() == 4 && ac4.getHealth() == 0 && ac4.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    GuardianCraft gc5("", 32, 49, AircraftStatus::Airborne, "FighterRabbits", 0, 14, true, 0);
    AbductorCraft ac5("", 100, 49, AircraftStatus::Airborne, false, 24, 29);
    gc5 * ac5;
    if(gc5.getWeaponCount() == 0 && gc5.getKillCount() == 0 && ac5.getHealth() == 49 && ac5.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    GuardianCraft gc6("", 32, 59, AircraftStatus::Airborne, "FighterRabbits", 4, 18, true, 5);
    AbductorCraft ac6("", 100, 64, AircraftStatus::Airborne, false, 0, 29);
    AbductorCraft ac7("", 100, 6, AircraftStatus::Airborne, false, 0, 10);
    gc6 * ac6;
    gc6 * ac7;
    gc6 * ac7;
    gc6 * ac6;
    gc6 * ac6;
    gc6 * ac6;
    gc6 * ac7;
    if(gc6.getWeaponCount() == 0 && gc6.getKillCount() == 6 && ac6.getHealth() == 10 && ac6.getCurrentStatus() == AircraftStatus::Airborne && ac7.getHealth() == 0 && ac7.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 1;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Engagement Operator * : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testOutputStreamOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 12;

    GuardianCraft gc1("GRDN1", 42, 59, AircraftStatus::OnGround, "Missiles", 5, 50, false, 3);
    string expectedOutput1 = "Identifier: GRDN1\n"
                             "Fuel Level: 42%\n"
                             "Health: 59%\n"
                             "Current Status: On Ground\n"
                             "Weapon Type: Missiles\n"
                             "Weapon Count: 5\n"
                             "Weapon Strength: 50\n"
                             "Cloak Status: Off\n"
                             "Kill Count: 3\n";
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << gc1;
    string actualOutput1 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput1 == expectedOutput1) {
        tempmarks += 4;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    GuardianCraft gc2("PatrolGuard", 33, 33, AircraftStatus::Airborne, "Rockets", 3, 20, true, 0);
    string expectedOutput2 = "Identifier: PatrolGuard\n"
                             "Fuel Level: 33%\n"
                             "Health: 33%\n"
                             "Current Status: Airborne\n"
                             "Weapon Type: Rockets\n"
                             "Weapon Count: 3\n"
                             "Weapon Strength: 20\n"
                             "Cloak Status: On\n"
                             "Kill Count: 0\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << gc2;
    string actualOutput2 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput2 == expectedOutput2) {
        tempmarks += 4;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    GuardianCraft gc3("WorldsWorstGuardian", 100, 0, AircraftStatus::Crashed, "LiterallyNothing", 0, 0, false, 0);
    string expectedOutput3 = "Identifier: WorldsWorstGuardian\n"
                             "Fuel Level: 100%\n"
                             "Health: 0%\n"
                             "Current Status: Crashed\n"
                             "Weapon Type: LiterallyNothing\n"
                             "Weapon Count: 0\n"
                             "Weapon Strength: 0\n"
                             "Cloak Status: Off\n"
                             "Kill Count: 0\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << gc3;
    string actualOutput3 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput3 == expectedOutput3) {
        tempmarks += 4;
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

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 28;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting GuardianCraft Operator Overloading Tests..." << RESET << endl << endl;

    testEngagementCriteriaOperator(marks);
    cout << endl;
    testEngagementOperator(marks);
    cout << endl;
    testOutputStreamOperator(marks);
    cout << endl;

    if(marks == TOTAL_MARKS) {
        cout << GREEN << "GuardianCraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    else {
        cout << RED << "GuardianCraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    cout << "----------------------------------\n";
}