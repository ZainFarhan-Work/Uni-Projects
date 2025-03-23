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

void testAircraftStatusOperator(float& marks) {

    AircraftStatus st1 = AircraftStatus::Airborne;
    string expectedOutput1 = "Airborne";
    stringstream buffer;
    streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << st1;
    string actualOutput1 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput1 == expectedOutput1) {
        marks += 0.8;
        cout << "Test 1 Passed.\n";
    }
    else {
        cout << "Test 1 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    AircraftStatus st2 = AircraftStatus::OnGround;
    string expectedOutput2 = "On Ground";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << st2;
    string actualOutput2 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput2 == expectedOutput2) {
        marks += 0.6;
        cout << "Test 2 Passed.\n";
    }
    else {
        cout << "Test 2 Failed.\n";
    }
    buffer.str("");
    buffer.clear();

    AircraftStatus st3 = AircraftStatus::Crashed;
    string expectedOutput3 = "Crashed";
    oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());
    cout << st3;
    string actualOutput3 = buffer.str();
    cout.rdbuf(oldCoutBuffer);
    if(actualOutput3 == expectedOutput3) {
        marks += 0.6;
        cout << "Test 3 Passed.\n";
    }
    else {
        cout << "Test 3 Failed.\n";
    }
}

int main() {
    float marks = 0;
    const int TOTAL_MARKS = 2;
    cout << "----------------------------------\n";
    cout << BLUE << "Starting Aircraft Status Operator Overloading Tests..." << RESET << endl << endl;
    testAircraftStatusOperator(marks);
    cout << endl;
    if(marks >= TOTAL_MARKS-0.1) {
        cout << GREEN << "Aircraft Status Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    else {
        cout << RED << "Aircraft Status Operator Overloading Results: " << marks << "/" << TOTAL_MARKS << RESET << endl;
    }
    cout << "----------------------------------\n";
}