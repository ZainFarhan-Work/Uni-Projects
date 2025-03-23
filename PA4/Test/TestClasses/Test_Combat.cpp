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

void testConstructors(int &marks) {
    int tempmarks = 0;
    int temptotal = 12;
    bool essential_parameterized, essential_copy;

    CombatAircraft ca1; 
    if(ca1.getIdentifier() == "" && ca1.getFuelLevel() == 100 && ca1.getHealth() == 100 && ca1.getCurrentStatus() == AircraftStatus::OnGround && ca1.getWeaponType() == "" && ca1.getWeaponCount() == 0 && ca1.getWeaponStrength() == 0) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    CombatAircraft ca2("CMBT2", 80, 43, AircraftStatus::Airborne, "Rockets", 10, 32);
    if(ca2.getIdentifier() == "CMBT2" && ca2.getFuelLevel() == 80 && ca2.getHealth() == 43 && ca2.getCurrentStatus() == AircraftStatus::Airborne && ca2.getWeaponType() == "Rockets" && ca2.getWeaponCount() == 10 && ca2.getWeaponStrength() == 32) {
        tempmarks += 2;
        essential_parameterized = true;
        cout << "Test 2 Passed.\n";
    }
    else {
        essential_parameterized = false;
        cout << "Test 2 Failed.\n";
    }

    CombatAircraft ca3(ca2);
    if(ca3.getIdentifier() == "CMBT2" && ca3.getFuelLevel() == 80 && ca3.getHealth() == 43 && ca3.getCurrentStatus() == AircraftStatus::Airborne && ca3.getWeaponType() == "Rockets" && ca3.getWeaponCount() == 10 && ca3.getWeaponStrength() == 32) {
        tempmarks += 2;
        essential_copy = true;
        cout << "Test 3 Passed.\n";
    }
    else {
        essential_copy = false;
        cout << "Test 3 Failed.\n";
    }

    CombatAircraft ca4("CMBT4", -2, 100, AircraftStatus::OnGround, "Missiles", 0, 80);
    if(ca4.getIdentifier() == "CMBT4" && ca4.getFuelLevel() == 0 && ca4.getHealth() == 100 && ca4.getCurrentStatus() == AircraftStatus::OnGround && ca4.getWeaponType() == "Missiles" && ca4.getWeaponCount() == 0 && ca4.getWeaponStrength() == 80) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    CombatAircraft ca5("CMBT5", 80, 0, AircraftStatus::Airborne, "Bombs", 12, 200);
    if(ca5.getIdentifier() == "CMBT5" && ca5.getFuelLevel() == 80 && ca5.getHealth() == 0 && ca5.getCurrentStatus() == AircraftStatus::Crashed && ca5.getWeaponType() == "Bombs" && ca5.getWeaponCount() == 12 && ca5.getWeaponStrength() == 100) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    CombatAircraft ca6("CMBT6", 112, 105, AircraftStatus::OnGround, "Rockets", -5, -32);
    if(ca6.getIdentifier() == "CMBT6" && ca6.getFuelLevel() == 100 && ca6.getHealth() == 100 && ca6.getCurrentStatus() == AircraftStatus::OnGround&& ca6.getWeaponType() == "Rockets" && ca6.getWeaponCount() == 0 && ca6.getWeaponStrength() == 0) {
        tempmarks += 2;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }
    
    marks += tempmarks;
    if(essential_parameterized && essential_copy) {
        cout << GREEN << "Essential Constructor Tests Passsed.\n" << RESET;
    }
    else {
        cout << RED << "Essential Constructor Tests Failed. Following constructors failed which subsequent tests rely on:\n";
        if (!essential_parameterized) cout << "- Parameterized Constructor (where all values passed are valid)\n";
        if (!essential_copy) cout << "- Copy Constructor\n";
        cout << RESET;
    }
    cout << YELLOW << "CombatAircraft Constructors: " << tempmarks << "/" << temptotal << endl << RESET;
}

void testFunctionalities(int &marks) {
    int tempmarks = 0;
    int temptotal = 8;

    CombatAircraft ca1("", 92, 87, AircraftStatus::OnGround, "", 0, 0);
    ca1.takeOff();
    if(ca1.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    CombatAircraft ca2("", 100, 72, AircraftStatus::Airborne, "", 0, 0);
    ca2.land();
    if(ca2.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    CombatAircraft ca3("", 29, 100, AircraftStatus::OnGround, "", 0, 0);
    ca3.land();
    ca3.takeOff();
    if(ca3.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    CombatAircraft ca4("", 24, 100, AircraftStatus::Crashed, "", 0, 0);
    ca4.takeOff();
    if(ca4.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    CombatAircraft ca5("", 30, 100, AircraftStatus::Crashed, "", 0, 0);
    ca5.land();
    if(ca5.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "CombatAircraft Functionalities: " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 20;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting CombatAircraft Tests..." << RESET << endl << endl;
    testConstructors(marks);
    cout << endl;
    testFunctionalities(marks);
    cout << endl;
    if(marks == TOTAL_MARKS) {
        cout << GREEN << "CombatAircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    else {
        cout << RED << "CombatAircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    cout << "----------------------------------\n";
}