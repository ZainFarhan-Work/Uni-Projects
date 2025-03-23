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
    int temptotal = 10;
    bool essential_parameterized, essential_copy;

    StealthAircraft sa1; 
    if(sa1.getIdentifier() == "" && sa1.getFuelLevel() == 100 && sa1.getHealth() == 100 && sa1.getCurrentStatus() == AircraftStatus::OnGround && sa1.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    StealthAircraft sa2("STLTH1", 80, 43, AircraftStatus::Airborne, true);
    if(sa2.getIdentifier() == "STLTH1" && sa2.getFuelLevel() == 80 && sa2.getHealth() == 43 && sa2.getCurrentStatus() == AircraftStatus::Airborne && sa2.getCloakStatus() == true) {
        tempmarks += 1;
        essential_parameterized = true;
        cout << "Test 2 Passed.\n";
    }
    else {
        essential_parameterized = false;
        cout << "Test 2 Failed.\n";
    }

    StealthAircraft sa3(sa2);
    if(sa3.getIdentifier() == "STLTH1" && sa3.getFuelLevel() == 80 && sa3.getHealth() == 43 && sa3.getCurrentStatus() == AircraftStatus::Airborne && sa3.getCloakStatus() == true) {
        tempmarks += 2;
        essential_copy = true;
        cout << "Test 3 Passed.\n";
    }
    else {
        essential_copy = false;
        cout << "Test 3 Failed.\n";
    }

    StealthAircraft sa4("STLTH4", -2, 100, AircraftStatus::OnGround, true);
    if(sa4.getIdentifier() == "STLTH4" && sa4.getFuelLevel() == 0 && sa4.getHealth() == 100 && sa4.getCurrentStatus() == AircraftStatus::OnGround && sa4.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    StealthAircraft sa5("STLTH5", 0, 80, AircraftStatus::Airborne, true);
    if(sa5.getIdentifier() == "STLTH5" && sa5.getFuelLevel() == 0 && sa5.getHealth() == 0 && sa5.getCurrentStatus() == AircraftStatus::Crashed && sa5.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    StealthAircraft sa6(sa5);
    if(sa6.getIdentifier() == "STLTH5" && sa6.getFuelLevel() == 0 && sa6.getHealth() == 0 && sa6.getCurrentStatus() == AircraftStatus::Crashed && sa6.getCloakStatus() == false) {
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
    cout << YELLOW << "StealthAircraft Constructors: " << tempmarks << "/" << temptotal << endl << RESET;
}

void testFunctionalities(int &marks) {
    int tempmarks = 0;
    int temptotal = 10;

    StealthAircraft sa1("", 100, 100, AircraftStatus::Airborne, false);
    sa1.activateCloak();
    if(sa1.getFuelLevel() == 85 && sa1.getHealth() == 90 && sa1.getCurrentStatus() == AircraftStatus::Airborne && sa1.getCloakStatus() == true) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    StealthAircraft sa2("", 35, 80, AircraftStatus::Airborne, true);
    sa2.deactivateCloak();
    if(sa2.getFuelLevel() == 35 && sa2.getHealth() == 80 && sa2.getCurrentStatus() == AircraftStatus::Airborne && sa2.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    StealthAircraft sa3("", 75, 83, AircraftStatus::Airborne, true);
    sa3.land();
    if(sa3.getFuelLevel() == 75 && sa3.getHealth() == 83 && sa3.getCurrentStatus() == AircraftStatus::OnGround && sa3.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    StealthAircraft sa7("", 75, 83, AircraftStatus::OnGround, false);
    sa7.takeOff();
    sa7.activateCloak();
    if(sa7.getFuelLevel() == 60 && sa7.getHealth() == 73 && sa7.getCurrentStatus() == AircraftStatus::Airborne && sa7.getCloakStatus() == true) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    StealthAircraft sa6("", 100, 0, AircraftStatus::Crashed, false);
    sa6.activateCloak();
    if(sa6.getFuelLevel() == 100 && sa6.getHealth() == 0 && sa6.getCurrentStatus() == AircraftStatus::Crashed && sa6.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    StealthAircraft sa4("", 15, 10, AircraftStatus::Airborne, false);
    sa4.activateCloak();
    if(sa4.getFuelLevel() == 15 && sa4.getHealth() == 0 && sa4.getCurrentStatus() == AircraftStatus::Crashed && sa4.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    StealthAircraft sa5("", 60, 30, AircraftStatus::OnGround, false);
    sa5.takeOff();
    sa5.activateCloak();
    sa5.land();
    sa5.takeOff();
    sa5.activateCloak();
    sa5.deactivateCloak();
    sa5.activateCloak();
    sa5.activateCloak();
    sa5.land();
    if(sa5.getFuelLevel() == 30 && sa5.getHealth() == 0 && sa5.getCurrentStatus() == AircraftStatus::Crashed && sa5.getCloakStatus() == false) {
        tempmarks += 3;
    }

    marks += tempmarks;
    cout << YELLOW << "StealthAircraft Functionalities: " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 20;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting StealthAircraft Tests..." << RESET << endl << endl;
    testConstructors(marks);
    cout << endl;
    testFunctionalities(marks);
    cout << endl;
    if(marks == TOTAL_MARKS) {
        cout << GREEN << "StealthAircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    else {
        cout << RED << "StealthAircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    cout << "----------------------------------\n";
}