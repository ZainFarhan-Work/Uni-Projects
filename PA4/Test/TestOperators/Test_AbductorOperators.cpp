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

void testAbducteeRatioOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 6;

    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, false, 50, 250);
    AbductorCraft ac2("", 100, 100, AircraftStatus::Airborne, true, 321, 963);
    AbductorCraft ac3("", 100, 100, AircraftStatus::OnGround, false, 32, 49);
    AbductorCraft ac4("", 100, 100, AircraftStatus::OnGround, false, 134, 402);
    
    if(ac2 > ac1) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }


    if(!(ac2 > ac3)) {
        tempmarks += 2;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    if(!(ac2>ac4) && !(ac4>ac2)) {
        tempmarks += 2;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Abductee Ratio Operator > : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testAbductOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;

    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, true, 33, 46);
    ac1 += 10;
    if(ac1.getAbducteeCount() == 43 && ac1.getAbducteeCapacity() == 46) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    AbductorCraft ac2("", 100, 100, AircraftStatus::OnGround, false, 10, 15);
    ac2 += 4;
    if(ac2.getAbducteeCount() == 10 && ac2.getAbducteeCapacity() == 15) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac3("", 100, 100, AircraftStatus::Airborne, false, 4, 9);
    ac3 += 6;
    if(ac3.getAbducteeCount() == 9 && ac3.getAbducteeCapacity() == 9) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Abduct Operator += : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testReleaseOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 4;

    AbductorCraft ac1("", 100, 100, AircraftStatus::Airborne, true, 29, 60);
    ac1 -= 24;
    if(ac1.getAbducteeCount() == 5 && ac1.getAbducteeCapacity() == 60) {
        tempmarks += 2;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }

    AbductorCraft ac2("", 100, 0, AircraftStatus::OnGround, false, 10, 30);
    ac2 -= 10;
    if(ac2.getAbducteeCount() == 10 && ac2.getAbducteeCapacity() == 30) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }

    AbductorCraft ac3("", 100, 100, AircraftStatus::Airborne, false, 19, 28);
    ac3 -= 24;
    if(ac3.getAbducteeCount() == 0 && ac3.getAbducteeCapacity() == 28) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Release Operator -= : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testMergeOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 10;

    AbductorCraft ac1("Abductor1", 35, 49, AircraftStatus::Airborne, true, 10, 10);
    AbductorCraft ac2("Abductor2", 42, 16, AircraftStatus::Airborne, true, 2, 5);
    ac1 & ac2;
    if(ac1.getFuelLevel() == 77 && ac1.getHealth() == 65) {
        tempmarks += 1;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    if(ac1.getAbducteeCount() == 12 && ac1.getAbducteeCapacity() == 15) {
        tempmarks += 1;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    if(ac2.getFuelLevel() == 0 && ac2.getHealth() == 0 && ac2.getCurrentStatus() == AircraftStatus::Crashed && ac2.getCloakStatus() == false && ac2.getAbducteeCount() == 0 && ac2.getAbducteeCapacity() == 0) {
        tempmarks += 1;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }

    AbductorCraft ac3("Abductor3", 10, 23, AircraftStatus::Airborne, false, 12, 32);
    AbductorCraft ac4("Abductor4", 32, 49, AircraftStatus::Airborne, false, 92, 112);
    ac3 & ac4;
    if(ac3.getFuelLevel() == 0 && ac3.getHealth() == 0 && ac3.getCurrentStatus() == AircraftStatus::Crashed && ac3.getAbducteeCount() == 0 && ac3.getAbducteeCapacity() == 0 && ac4.getFuelLevel() == 42 && ac4.getHealth() == 72 && ac4.getCurrentStatus() == AircraftStatus::Airborne && ac4.getAbducteeCount() == 104 && ac4.getAbducteeCapacity() == 144) {
        tempmarks += 2;
        cout << "Test 4 Passed.\n";
    }
    else {
        cout << "Test 4 Failed.\n";
    }

    AbductorCraft ac5("Abductor5", 29, 68, AircraftStatus::Airborne, false, 0, 25);
    AbductorCraft ac6("Abductor6", 67, 35, AircraftStatus::Airborne, true, 14, 14);
    ac5 & ac6;
    if(ac5.getFuelLevel() == 96 && ac5.getHealth() == 100 && ac5.getAbducteeCount() == 14 && ac5.getAbducteeCapacity() == 39 && ac6.getFuelLevel() == 0 && ac6.getHealth() == 0 && ac6.getCurrentStatus() == AircraftStatus::Crashed && ac6.getAbducteeCount() == 0 && ac6.getAbducteeCapacity() == 0) {
        tempmarks += 2;
        cout << "Test 5 Passed.\n";
    }
    else {
        cout << "Test 5 Failed.\n";
    }

    AbductorCraft ac7("Abductor7", 39, 44, AircraftStatus::OnGround, false, 12, 50);
    AbductorCraft ac8("Abductor8", 24, 21, AircraftStatus::Airborne, true, 33, 54);
    ac7 & ac8;
    if(ac7.getFuelLevel() == 39 && ac7.getHealth() == 44 && ac7.getAbducteeCount() == 12 && ac7.getAbducteeCapacity() == 50 && ac8.getFuelLevel() == 24 && ac8.getHealth() == 21 && ac8.getAbducteeCount() == 33 && ac8.getAbducteeCapacity() == 54) {
        tempmarks += 1;
        cout << "Test 6 Passed.\n";
    }
    else {
        cout << "Test 6 Failed.\n";
    }

    AbductorCraft ac9("Abductor9", 53, 76, AircraftStatus::Airborne, true, 25, 25);
    AbductorCraft ac10("Abductor10", 49, 63, AircraftStatus::Airborne, false, 23, 41);
    ac9 & ac10;
    if(ac9.getFuelLevel() == 0 && ac9.getHealth() == 0 && ac9.getCurrentStatus() == AircraftStatus::Crashed && ac9. getAbducteeCount() == 0 && ac9.getAbducteeCapacity() == 0 && ac10.getFuelLevel() == 100 && ac10.getHealth() == 100 && ac10.getAbducteeCount() == 48 && ac10.getAbducteeCapacity() == 66) {
        tempmarks += 2;
        cout << "Test 7 Passed.\n";
    }
    else {
        cout << "Test 7 Failed.\n";
    }

    marks += tempmarks;
    cout << YELLOW << "Merge Operator & : " << tempmarks << "/" << temptotal << endl << RESET;
}

void testOutputStreamOperator(int &marks) {
    int tempmarks = 0;
    int temptotal = 6;

    AbductorCraft ac1("ABDCT1", 23, 34, AircraftStatus::OnGround, false, 6, 12);
    string expectedOutput1 = "Identifier: ABDCT1\n"
                             "Fuel Level: 23%\n"
                             "Health: 34%\n"
                             "Current Status: On Ground\n"
                             "Cloak Status: Off\n"
                             "Abductee Count: 6\n"
                             "Abductee Capacity: 12\n";
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ac1;
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

    AbductorCraft ac2("HiddenAbductorInTheAir", 94, 99, AircraftStatus::Airborne, true, 12, 20);
    string expectedOutput2 = "Identifier: HiddenAbductorInTheAir\n"
                             "Fuel Level: 94%\n"
                             "Health: 99%\n"
                             "Current Status: Airborne\n"
                             "Cloak Status: On\n"
                             "Abductee Count: 12\n"
                             "Abductee Capacity: 20\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ac2;
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

    AbductorCraft ac3("AbductorCaughtAStray", 0, 0, AircraftStatus::Crashed, false, 0, 0);
    string expectedOutput3 = "Identifier: AbductorCaughtAStray\n"
                             "Fuel Level: 0%\n"
                             "Health: 0%\n"
                             "Current Status: Crashed\n"
                             "Cloak Status: Off\n"
                             "Abductee Count: 0\n"
                             "Abductee Capacity: 0\n";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << ac3;
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
    const int TOTAL_MARKS = 30;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting AbductorCraft Operator Overloading Tests..." << RESET << endl << endl;

    testAbducteeRatioOperator(marks);
    cout << endl;
    testAbductOperator(marks);
    cout << endl;
    testReleaseOperator(marks);
    cout << endl;
    testMergeOperator(marks);
    cout << endl;
    testOutputStreamOperator(marks);
    cout << endl;

    if(marks == TOTAL_MARKS) {
        cout << GREEN << "AbductorCraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << GREEN << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    else {
        cout << RED << "AbductorCraft Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
        cout << RED << "Scaled Results: " << static_cast<float>(marks)/2 << "/" << TOTAL_MARKS/2 << RESET << endl;
    }
    cout << "----------------------------------\n";
}