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

    GuardianCraft gc1;
    if(gc1.getIdentifier() == "" && gc1.getFuelLevel() == 100 && gc1.getHealth() == 100 && gc1.getCurrentStatus() == AircraftStatus::OnGround && gc1.getWeaponType() == "" && gc1.getWeaponCount() == 0 && gc1.getWeaponStrength() == 0 && gc1.getCloakStatus() == false && gc1.getKillCount() == 0) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc2("GRD1", 25, 69, AircraftStatus::Airborne, "Llamas", 10, 25, true, 2);
    if(gc2.getIdentifier() == "GRD1" && gc2.getFuelLevel() == 25 && gc2.getHealth() == 69 && gc2.getCurrentStatus() == AircraftStatus::Airborne && gc2.getWeaponType() == "Llamas" && gc2.getWeaponCount() == 10 && gc2.getWeaponStrength() == 25 && gc2.getCloakStatus() == true && gc2.getKillCount() == 2) {
        tempmarks += 2;
        essential_parameterized = true;
        cout << "Test 2 Passed.\n";
    }
    else {
        essential_parameterized = false;
        cout << "Test 2 Failed.\n";
    }
    GuardianCraft gc3(gc2);
    if(gc3.getIdentifier() == "GRD1" && gc3.getFuelLevel() == 25 && gc3.getHealth() == 69 && gc3.getCurrentStatus() == AircraftStatus::Airborne && gc3.getWeaponType() == "Llamas" && gc3.getWeaponCount() == 10 && gc3.getWeaponStrength() == 25 && gc3.getCloakStatus() == true && gc3.getKillCount() == 2) {
        tempmarks += 2;
        essential_copy = true;
        cout << "Test 3 Passed.\n";
    }
    else {
        essential_copy = false;
        cout << "Test 3 Failed.\n";
    }

    GuardianCraft gc4("GRD4", -34, 150, AircraftStatus::OnGround, "Rockets", 12, 32, false, 20);
    if(gc4.getIdentifier() == "GRD4" && gc4.getFuelLevel() == 0 && gc4.getHealth() == 100 && gc4.getCurrentStatus() == AircraftStatus::OnGround && gc4.getWeaponType() == "Rockets" && gc4.getWeaponCount() == 12 && gc4.getWeaponStrength() == 32 && gc4.getCloakStatus() == false && gc4.getKillCount() == 20) {
        tempmarks += 2; 
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    GuardianCraft gc5("GRD5", 73, 99, AircraftStatus::Airborne, "Mega Rocket", 1, 100, true, -23);
    if(gc5.getIdentifier() == "GRD5" && gc5.getFuelLevel() == 73 && gc5.getHealth() == 99 && gc5.getCurrentStatus() == AircraftStatus::Airborne && gc5.getWeaponType() == "Mega Rocket" && gc5.getWeaponCount() == 1 && gc5.getWeaponStrength() == 100 && gc5.getCloakStatus() == true && gc5.getKillCount() == 0) {
        tempmarks += 3;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    GuardianCraft gc6("GRD6", 45, -32, AircraftStatus::OnGround, "Rocks", 1000, 1, false, 0);
    if(gc6.getIdentifier() == "GRD6" && gc6.getFuelLevel() == 45 && gc6.getHealth() == 0 && gc6.getCurrentStatus() == AircraftStatus::Crashed && gc6.getWeaponType() == "Rocks" && gc6.getWeaponCount() == 1000 && gc6.getWeaponStrength() == 1 && gc6.getCloakStatus() == false && gc6.getKillCount() == 0) {
        tempmarks += 3;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    GuardianCraft gc7("GRD7", 0, 1, AircraftStatus::Airborne, "Punches", 5, 20, true, 0);
    if(gc7.getIdentifier() == "GRD7" && gc7.getFuelLevel() == 0 && gc7.getHealth() == 0 && gc7.getCurrentStatus() == AircraftStatus::Crashed && gc7.getWeaponType() == "Punches" && gc7.getWeaponCount() == 5 && gc7.getWeaponStrength() == 20 && gc7.getCloakStatus() == false && gc7.getKillCount() == 0) {
        tempmarks += 3;
        cout << "Test 7 Passed.\n";
    }
    else {
        cout << "Test 7 Failed.\n";
    }

    GuardianCraft gc8("GRD8", 100, 43, AircraftStatus::OnGround, "Punches", 5, 20, true, 0);
    if(gc8.getIdentifier() == "GRD8" && gc8.getFuelLevel() == 100 && gc8.getHealth() == 43 && gc8.getCurrentStatus() == AircraftStatus::OnGround && gc8.getWeaponType() == "Punches" && gc8.getWeaponCount() == 5 && gc8.getWeaponStrength() == 20 && gc8.getCloakStatus() == false && gc8.getKillCount() == 0) {
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
    cout << YELLOW << "GuardianCraft Constructors: " << tempmarks << "/" << temptotal << endl << RESET;
}

void testFunctionalities(int &marks) {
    int tempmarks = 0;
    int temptotal = 20;

    GuardianCraft gc1("", 80, 69, AircraftStatus::Airborne, "", 0, 0, false, 5);
    gc1.activateCloak();
    gc1.activateCloak();
    if(gc1.getFuelLevel() == 65 && gc1.getHealth() == 59 && gc1.getCurrentStatus() == AircraftStatus::Airborne && gc1.getCloakStatus() == true && gc1.getKillCount() == 5) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    GuardianCraft gc2("", 30, 32, AircraftStatus::Airborne, "", 0, 0, true, 4);
    gc2.deactivateCloak();
    if(gc2.getFuelLevel() == 30 && gc2.getHealth() == 32 && gc2.getCurrentStatus() == AircraftStatus::Airborne && gc2.getCloakStatus() == false && gc2.getKillCount() == 4) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    GuardianCraft gc3("", 29, 49, AircraftStatus::OnGround, "", 0, 0, false, 4);
    gc3.takeOff();
    if(gc3.getFuelLevel() == 29 && gc3.getHealth() == 49 && gc3.getCurrentStatus() == AircraftStatus::OnGround && gc3.getCloakStatus() == false && gc3.getKillCount() == 4) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    GuardianCraft gc4("", 90, 90, AircraftStatus::Airborne, "", 0, 0, true, 5);
    gc4.land();
    if(gc4.getFuelLevel() == 90 && gc4.getHealth() == 90 && gc4.getCurrentStatus() == AircraftStatus::OnGround && gc4.getCloakStatus() == false && gc4.getKillCount() == 5) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    GuardianCraft gc5("", 31, 0, AircraftStatus::Crashed, "", 0, 0, false, 5);
    gc5.takeOff();
    gc5.activateCloak();
    if(gc5.getFuelLevel() == 31 && gc5.getHealth() == 0 && gc5.getCurrentStatus() == AircraftStatus::Crashed && gc5.getCloakStatus() == false && gc5.getKillCount() == 5) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    GuardianCraft gc6("", 15, 20, AircraftStatus::Airborne, "", 0, 0, true, 3);
    gc6.deactivateCloak();
    gc6.activateCloak();
    if(gc6.getFuelLevel() == 0 && gc6.getHealth() == 0 && gc6.getCurrentStatus() == AircraftStatus::Crashed && gc6.getCloakStatus() == false && gc6.getKillCount() == 3) {
        tempmarks += 4;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    GuardianCraft gc7("", 60, 30, AircraftStatus::OnGround, "", 0, 0, false, 8);
    gc7.activateCloak();
    gc7.takeOff();
    gc7.activateCloak(); // 45, 20
    gc7.land();
    gc7.takeOff();
    gc7.activateCloak(); // 30, 10
    gc7.deactivateCloak();
    gc7.activateCloak();
    gc7.activateCloak();
    gc7.land();
    if(gc7.getFuelLevel() == 30 && gc7.getHealth() == 0 && gc7.getCurrentStatus() == AircraftStatus::Crashed && gc7.getCloakStatus() == false && gc7.getKillCount() == 8) {
        tempmarks += 6;
        cout << "Test 7 Passed.\n";
    }
    else {
        cout << "Test 7 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "GuardianCraft Functionalities: " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 40;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting GuardianCraft Tests..." << RESET << endl << endl;
    testConstructors(marks);
    cout << endl;
    testFunctionalities(marks);
    cout << endl;
    if(marks == TOTAL_MARKS) {
        cout << GREEN << "GuardianCraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    else {
        cout << RED << "GuardianCraft Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/4 << "/" << TOTAL_MARKS/4 << RESET << endl;
    }
    cout << "----------------------------------\n";
}