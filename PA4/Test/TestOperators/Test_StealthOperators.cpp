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

void testCloakStatusOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;

    StealthAircraft sa1("", 82, 43, AircraftStatus::Airborne, false);
    !sa1;
    if(sa1.getFuelLevel() == 67 && sa1.getHealth() == 33 && sa1.getCloakStatus() == true) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    AbductorCraft ac1("", 23, 100, AircraftStatus::OnGround, false, 0, 200);
    !ac1;
    if(ac1.getFuelLevel() == 23 && ac1.getHealth() == 100 && ac1.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    GuardianCraft gc1("", 15, 10, AircraftStatus::Airborne, "", 0, 0, false, 5);
    !gc1;
    if(gc1.getFuelLevel() == 15 && gc1.getHealth() == 0 && gc1.getCurrentStatus() == AircraftStatus::Crashed && gc1.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    AbductorCraft ac2("", 42, 60, AircraftStatus::Airborne, false, 0, 200);
    !ac2;
    !ac2;
    !ac2;
    !ac2;
    !ac2;
    !ac2;
    if(ac2.getFuelLevel() == 0 && ac2.getHealth() == 0 && ac2.getCurrentStatus() == AircraftStatus::Crashed && ac2.getCloakStatus() == false) {
        tempmarks += 1;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Cloak Status Operator ! : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testOutputStreamOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 6;

    StealthAircraft sa1("STEALTH1", 78, 42, AircraftStatus::Airborne, true);
    string expectedOutput1 = "Identifier: STEALTH1\n"
                             "Fuel Level: 78%\n"
                             "Health: 42%\n"
                             "Current Status: Airborne\n"
                             "Cloak Status: On\n";
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << sa1;
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

    StealthAircraft sa2("NotQuiteHidden", 33, 33, AircraftStatus::OnGround, false);
    string expectedOutput2 = "Identifier: NotQuiteHidden\n"
                             "Fuel Level: 33%\n"
                             "Health: 33%\n"
                             "Current Status: On Ground\n"
                             "Cloak Status: Off\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << sa2;
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

    StealthAircraft sa3("DefinitelyNotHidden", 49, 0, AircraftStatus::Crashed, false);
    string expectedOutput3 = "Identifier: DefinitelyNotHidden\n"
                             "Fuel Level: 49%\n"
                             "Health: 0%\n"
                             "Current Status: Crashed\n"
                             "Cloak Status: Off\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << sa3;
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
    cout << YELLOW << "Output Stream Operator << : " << tempmarks << "/" << temptotal << endl << RESET;
}

int main() {
    int marks = 0;
    const int TOTAL_MARKS = 10;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting StealthAircraft Operator Overloading Tests..." << RESET << endl << endl;

    testCloakStatusOperator(marks);
    cout << endl;
    testOutputStreamOperator(marks);
    cout << endl;

    if(marks == TOTAL_MARKS) {
        cout << GREEN << "StealthAircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    else {
        cout << RED << "StealthAircraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    cout << "----------------------------------\n";
}