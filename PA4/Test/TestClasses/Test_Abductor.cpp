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
    int temptotal = 20;
    bool essential_parameterized, essential_copy;
    
    AbductorCraft ac1;
    if(ac1.getIdentifier() == "" && ac1.getFuelLevel() == 100 && ac1.getHealth() == 100 && ac1.getCurrentStatus() == AircraftStatus::OnGround && ac1.getCloakStatus() == false && ac1.getAbducteeCount() == 0 && ac1.getAbducteeCapacity() == 0) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    AbductorCraft ac2("ABDT1", 43, 90, AircraftStatus::Airborne, true, 23, 34);
    if(ac2.getIdentifier() == "ABDT1" && ac2.getFuelLevel() == 43 && ac2.getHealth() == 90 && ac2.getCurrentStatus() == AircraftStatus::Airborne && ac2.getCloakStatus() == true && ac2.getAbducteeCount() == 23 && ac2.getAbducteeCapacity() == 34) {
        tempmarks += 2;
        essential_parameterized = true;
        cout << "Test 2 Passed.\n";
    }
    else {
        essential_parameterized = false;
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac3(ac2);
    if(ac3.getIdentifier() == "ABDT1" && ac3.getFuelLevel() == 43 && ac3.getHealth() == 90 && ac3.getCurrentStatus() == AircraftStatus::Airborne && ac3.getCloakStatus() == true && ac3.getAbducteeCount() == 23 && ac3.getAbducteeCapacity() == 34) {
        tempmarks += 2;
        essential_copy = true;
        cout << "Test 3 Passed.\n";
    }
    else {
        essential_copy = false;
        cout << "Test 3 Failed.\n";
    }

    AbductorCraft ac5("ABDT5", -4, 1000, AircraftStatus::OnGround, false, 1, 7);
    if(ac5.getIdentifier() == "ABDT5" && ac5.getFuelLevel() == 0 && ac5.getHealth() == 100 && ac5.getCurrentStatus() == AircraftStatus::OnGround && ac5.getCloakStatus() == false && ac5.getAbducteeCount() == 1 && ac5.getAbducteeCapacity() == 7) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    AbductorCraft ac4("ABDT4", 34, 53, AircraftStatus::OnGround, false, 3, -2);
    if(ac4.getIdentifier() == "ABDT4" && ac4.getFuelLevel() == 34 && ac4.getHealth() == 53 && ac4.getCurrentStatus() == AircraftStatus::OnGround && ac4.getCloakStatus() == false && ac4.getAbducteeCount() == 3 && ac4.getAbducteeCapacity() == 3) {
        tempmarks += 3;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    AbductorCraft ac6("ABDT6", 39, 87, AircraftStatus::OnGround, false, -12, 7);
    if(ac6.getIdentifier() == "ABDT6" && ac6.getFuelLevel() == 39 && ac6.getHealth() == 87 && ac6.getCurrentStatus() == AircraftStatus::OnGround && ac6.getCloakStatus() == false && ac6.getAbducteeCount() == 0 && ac6.getAbducteeCapacity() == 7) {
        tempmarks += 3;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    AbductorCraft ac7("ABDT7", 0, 87, AircraftStatus::Airborne, true, 5, 12);
    if(ac7.getIdentifier() == "ABDT7" && ac7.getFuelLevel() == 0 && ac7.getHealth() == 0 && ac7.getCurrentStatus() == AircraftStatus::Crashed && ac7.getCloakStatus() == false && ac7.getAbducteeCount() == 5 && ac7.getAbducteeCapacity() == 12) {
        tempmarks += 3;
        cout << "Test 7 Passed.\n";
    }
    else {
        cout << "Test 7 Failed.\n";
    }

    AbductorCraft ac8("ABDT8", 23, 53, AircraftStatus::OnGround, true, 0, 0);
    if(ac8.getIdentifier() == "ABDT8" && ac8.getFuelLevel() == 23 && ac8.getHealth() == 53 && ac8.getCurrentStatus() == AircraftStatus::OnGround && ac8.getCloakStatus() == false && ac8.getAbducteeCount() == 0 && ac8.getAbducteeCapacity() == 0) {
        tempmarks += 3;
        cout << "Test 8 Passed.\n";
    }
    else {
        cout << "Test 8 Failed.\n";
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
    cout << YELLOW << "AbductorCraft Constructors: " << tempmarks << "/" << temptotal << endl << RESET;
}

void testFunctionalities(int &marks) {
    int tempmarks = 0;
    int temptotal = 20;

    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, false, 0, 0);
    ac1.activateCloak();
    if(ac1.getFuelLevel() == 85 && ac1.getHealth() == 90 && ac1.getCurrentStatus() == AircraftStatus::Airborne && ac1.getCloakStatus() == true) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    AbductorCraft ac2("", 35, 80, AircraftStatus::Airborne, true, 0, 10);
    ac2.deactivateCloak();
    if(ac2.getFuelLevel() == 35 && ac2.getHealth() == 80 && ac2.getCurrentStatus() == AircraftStatus::Airborne && ac2.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac3("", 75, 83, AircraftStatus::Airborne, true, 10, 100);
    ac3.land();
    if(ac3.getFuelLevel() == 75 && ac3.getHealth() == 83 && ac3.getCurrentStatus() == AircraftStatus::OnGround && ac3.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    AbductorCraft ac7("", 75, 83, AircraftStatus::OnGround, false, 0, 0);
    ac7.takeOff();
    ac7.activateCloak();
    if(ac7.getFuelLevel() == 60 && ac7.getHealth() == 73 && ac7.getCurrentStatus() == AircraftStatus::Airborne && ac7.getCloakStatus() == true) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    AbductorCraft ac6("", 100, 0, AircraftStatus::Crashed, false, 2, 5);
    ac6.activateCloak();
    if(ac6.getFuelLevel() == 100 && ac6.getHealth() == 0 && ac6.getCurrentStatus() == AircraftStatus::Crashed && ac6.getCloakStatus() == false) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    AbductorCraft ac4("", 15, 10, AircraftStatus::Airborne, false, 3, 5);
    ac4.activateCloak();
    if(ac4.getFuelLevel() == 15 && ac4.getHealth() == 0 && ac4.getCurrentStatus() == AircraftStatus::Crashed && ac4.getCloakStatus() == false) {
        tempmarks += 4;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    AbductorCraft ac5("", 60, 30, AircraftStatus::OnGround, false, 1, 4);
    ac5.takeOff();
    ac5.activateCloak();
    ac5.land();
    ac5.takeOff();
    ac5.activateCloak();
    ac5.deactivateCloak();
    ac5.activateCloak();
    ac5.activateCloak();
    ac5.land();
    if(ac5.getFuelLevel() == 30 && ac5.getHealth() == 0 && ac5.getCurrentStatus() == AircraftStatus::Crashed && ac5.getCloakStatus() == false) {
        tempmarks += 6;
        cout << "Test 7 Passed.\n";
    }
    else {
        cout << "Test 7 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "AbductorCraft Functionalities: " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 40;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting AbductorCraft Tests..." << RESET << endl << endl;
    testConstructors(marks);
    cout << endl;
    testFunctionalities(marks);
    cout << endl;
    if(marks == TOTAL_MARKS) {
        cout << GREEN << "AbductorCraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    else {
        cout << RED << "AbductorCraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    cout << "----------------------------------\n";
}