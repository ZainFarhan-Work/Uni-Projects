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

void testRefuelOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;

    Aircraft a1("", 32, 95, AircraftStatus::OnGround);
    a1 += 39;
    if(a1.getFuelLevel() == 71 && a1.getHealth() == 95 && a1.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    CombatAircraft ca1("", 87, 99, AircraftStatus::Airborne, "", 12, 14);
    ca1 += 25;
    if(ca1.getFuelLevel() == 87 && ca1.getHealth() == 99 && ca1.getCurrentStatus() == AircraftStatus::Airborne && ca1.getWeaponCount() == 12 && ca1.getWeaponStrength() == 14) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac1("", 23, 100, AircraftStatus::OnGround, false, 0, 200);
    ac1 += 22;
    if(ac1.getFuelLevel() == 45 && ac1.getHealth() == 100 && ac1.getCurrentStatus() == AircraftStatus::OnGround && ac1.getAbducteeCapacity() == 200) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    GuardianCraft gc1("", 80, 92, AircraftStatus::OnGround, "", 0, 0, false, 5);
    gc1 += 25;
    if(gc1.getFuelLevel() == 100 && gc1.getHealth() == 92 && gc1.getCurrentStatus() == AircraftStatus::OnGround && gc1.getKillCount() == 5) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Refueling Operator += : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testDefuelOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;

    Aircraft a1("", 42, 98, AircraftStatus::Airborne);
    a1 -= 32;
    if(a1.getFuelLevel() == 42 && a1.getHealth() == 98  && a1.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    CombatAircraft ca1("", 99, 99, AircraftStatus::OnGround, "", 14, 14);
    ca1 -= 25;
    if(ca1.getFuelLevel() == 74 && ca1.getHealth() == 99 && ca1.getCurrentStatus() == AircraftStatus::OnGround && ca1.getWeaponCount() == 14 && ca1.getWeaponStrength() == 14) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac1("", 90, 100, AircraftStatus::OnGround, false, 0, 200);
    ac1 -= 80;
    if(ac1.getFuelLevel() == 10 && ac1.getHealth() == 100 && ac1.getCurrentStatus() == AircraftStatus::OnGround && ac1.getAbducteeCapacity() == 200) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    StealthAircraft sa1("", 32, 94, AircraftStatus::OnGround, false);
    sa1 -= 41;
    if(sa1.getFuelLevel() == 0 && sa1.getHealth() == 94 && sa1.getCurrentStatus() == AircraftStatus::OnGround && sa1.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Defueling Operator -= : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testEqualityOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;
    Aircraft a1("ACFT1", 83, 32, AircraftStatus::Airborne);
    Aircraft a2("ACFT2", 83, 32, AircraftStatus::Airborne);
    Aircraft a3("ACFT1", 32, 83, AircraftStatus::Airborne);
    Aircraft a4("ACFT1", 32, 83, AircraftStatus::OnGround);
    Aircraft a5("ACFT2", 83, 32, AircraftStatus::Airborne);

    if(a2 == a5) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    if(!(a1 == a2)) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    if(!(a1 == a3)) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    if(!(a3 == a4)) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Equality Operator == : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testOutputStreamOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 6;

    Aircraft a1("AIRCRFT1", 48, 93, AircraftStatus::OnGround);
    string expectedOutput1 = "Identifier: AIRCRFT1\n"
                             "Fuel Level: 48%\n"
                             "Health: 93%\n"
                             "Current Status: On Ground\n";
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << a1;
    string actualOutput1 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput1 == expectedOutput1) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    Aircraft a2("Planee", 23, 44, AircraftStatus::Airborne);
    string expectedOutput2 = "Identifier: Planee\n"
                             "Fuel Level: 23%\n"
                             "Health: 44%\n"
                             "Current Status: Airborne\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << a2;
    string actualOutput2 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput2 == expectedOutput2) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    Aircraft a3("AircraftNumber3", 45, 0, AircraftStatus::Crashed);
    string expectedOutput3 = "Identifier: AircraftNumber3\n"
                             "Fuel Level: 45%\n"
                             "Health: 0%\n"
                             "Current Status: Crashed\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << a3;
    string actualOutput3 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput3 == expectedOutput3) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    marks += tempmarks;
    cout << YELLOW "Output Stream Operator << : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testInputStreamOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 6;

    // acft only
    Aircraft a1;
    istringstream input1("FLY39 32 12 0");
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    input1 >> a1;
    cout.rdbuf(oldCoutBuffer);
    if(a1.getIdentifier() == "FLY39" && a1.getFuelLevel() == 32 && a1.getHealth() == 12 && a1.getCurrentStatus() == AircraftStatus::OnGround) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    buffer.str("");
    buffer.clear();


    Aircraft a2;
    istringstream input2("HighKite 22 99 1");
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    input2 >> a2;
    cout.rdbuf(oldCoutBuffer);
    if(a2.getIdentifier() == "HighKite" && a2.getFuelLevel() == 22 && a2.getHealth() == 99 && a2.getCurrentStatus() == AircraftStatus::Airborne) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    Aircraft a3;
    istringstream input3("GotPwned 45 0 2");
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    input3 >> a3;
    cout.rdbuf(oldCoutBuffer);
    if(a3.getIdentifier() == "GotPwned" && a3.getFuelLevel() == 45 && a3.getHealth() == 0 && a3.getCurrentStatus() == AircraftStatus::Crashed) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    marks += tempmarks;
    cout << YELLOW << "Input Stream Operator >> : " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 24;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting Aircraft Operator Overloading Tests..." << RESET << endl << endl;

    testRefuelOperator(marks);
    cout << endl;
    testDefuelOperator(marks);
    cout << endl;
    testEqualityOperator(marks);
    cout << endl;
    testOutputStreamOperator(marks);
    cout << endl;
    testInputStreamOperator(marks);
    cout << endl;

    if(marks == TOTAL_MARKS) {
        cout << GREEN << "Aircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    else {
        cout << RED << "Aircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    cout << "----------------------------------\n";
}