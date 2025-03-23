#include <iostream>
#include <sstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip> 
#include <cstdlib>
#include<type_traits>
#include "../../ACS_61.cpp"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"

void testConstructors(int &marks) {
    int tempmarks = 0;
    bool essential_parameterized, essential_copy;

    Aircraft a1; 
    if(a1.getIdentifier() == "" && a1.getFuelLevel() == 100 && a1.getHealth() == 100 && a1.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    
    Aircraft a2("ACFT2", 80, 43, AircraftStatus::Airborne);
    if(a2.getIdentifier() == "ACFT2" && a2.getFuelLevel() == 80 && a2.getHealth() == 43 && a2.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        essential_parameterized = true;
        cout << "Test 2 Passed.\n";
    }
    else {
        essential_parameterized = false;
        cout << "Test 2 Failed.\n";
    }

    Aircraft a3(a2);
    if(a3.getIdentifier() == "ACFT2" && a3.getFuelLevel() == 80 && a3.getHealth() == 43 && a3.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        essential_copy = true;
        cout << "Test 3 Passed.\n";
    }
    else {
        essential_copy = false;
        cout << "Test 3 Failed.\n";
    }

    Aircraft a4("ACFT4", -2, 100, AircraftStatus::OnGround);
    if(a4.getIdentifier() == "ACFT4" && a4.getFuelLevel() == 0 && a4.getHealth() == 100 && a4.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    Aircraft a5("ACFT5", 0, 100, AircraftStatus::Airborne);
    if(a5.getIdentifier() == "ACFT5" && a5.getFuelLevel() == 0 && a5.getHealth() == 0 && a5.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 1;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    Aircraft a6("ACFT6", 104, 120, AircraftStatus::OnGround);
    if(a6.getIdentifier() == "ACFT6" && a6.getFuelLevel() == 100 && a6.getHealth() == 100 && a6.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }
    
    marks += tempmarks;
    if(essential_parameterized && essential_copy) {
        cout << GREEN <<  "Essential Constructor Tests Passsed.\n" << RESET;
    }
    else {
        cout << RED << "Essential Constructor Tests Failed. Following constructors failed which subsequent tests rely on:\n";
        if (!essential_parameterized) cout << "- Parameterized Constructor (where all values passed are valid)\n";
        if (!essential_copy) cout << "- Copy Constructor\n";
        cout << RESET;
    }
    cout << YELLOW << "Aircraft Constructors: " << tempmarks << "/6\n" << RESET;
}

void testFunctionalities(int &marks) {
    int tempmarks = 0;

    Aircraft a1("", 100, 100, AircraftStatus::OnGround);
    a1.takeOff();
    if(a1.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    

    Aircraft a2("", 100, 100, AircraftStatus::Airborne);
    a2.land();
    if(a2.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    

    Aircraft a3("", 23, 100, AircraftStatus::OnGround);
    a3.land();
    a3.takeOff();
    if(a3.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }
    

    Aircraft a4("", 65, 100, AircraftStatus::Crashed);
    a4.land();
    a4.takeOff();
    if(a4.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }
    

    marks += tempmarks;
    cout << YELLOW << "Aircraft Functionalities: " << tempmarks << "/4\n" << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 10;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting Aircraft Tests..." << RESET << endl << endl;
    testConstructors(marks);
    cout << endl;
    testFunctionalities(marks);
    cout << endl;
    if(marks == TOTAL_MARKS) {
        cout << GREEN << "Aircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    else {
        cout << RED << "Aircraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    cout << "----------------------------------\n";
}