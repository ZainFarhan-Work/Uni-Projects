//// filepath: /f:/CS 200 TAship/CS_200_PA3s/NEWPA3/tests/test7.cpp
#include <iostream>
#include <sstream>
#include <string>
#include "../include/BattleHistory.hpp"
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

void printTestResult(const string &testName, bool passed, int points, const string &debugInfo = "") {
    if (passed)
        cout << COLOR_GREEN << "[PASSED] " << testName << " (" << points << " points)" << COLOR_RESET << endl;
    else {
        cout << COLOR_RED << "[FAILED] " << testName << " (0 points)" << COLOR_RESET << endl;
        if (!debugInfo.empty())
            cout << COLOR_YELLOW << "       Debug: " << debugInfo << COLOR_RESET << endl;
    }
}

int main() {
    int score = 0;
    cout << COLOR_BLUE << "=== Test 7: Testing BattleHistory Class ===" << COLOR_RESET << endl;

    // Create a BattleHistory object
    BattleHistory history;

    // 1. Add multiple logs to force expansion
    for (int i = 0; i < 15; i++) {
        history.addLog("Log entry " + to_string(i));
    }
    bool countOk = (history.getLogCount() == 15);
    {
        ostringstream debug;
        if (!countOk)
            debug << "Expected log count 15, but got " << history.getLogCount();
        printTestResult("Log Addition & Count", countOk, 1, debug.str());
    }
    score += countOk ? 1 : 0;

    // 2. Retrieve a specific log
    bool logEntryOk = (history.getLogAt(5) == "Log entry 5");
    {
        ostringstream debug;
        string retrieved = history.getLogAt(5);
        if (!logEntryOk)
            debug << "Expected 'Log entry 5', but got '" << retrieved << "'";
        printTestResult("Retrieve Specific Log", logEntryOk, 1, debug.str());
    }
    score += logEntryOk ? 1 : 0;

    // 3. Test deep copy via copy constructor
    BattleHistory copyHistory(history);
    copyHistory.addLog("New Log");
    bool deepCopyOk = (history.getLogCount() == 15 && copyHistory.getLogCount() == 16);
    {
        ostringstream debug;
        if (!deepCopyOk)
            debug << "Expected original count=15 and copy count=16, but got original count="
                  << history.getLogCount() << " and copy count=" << copyHistory.getLogCount();
        printTestResult("Copy Constructor Deep Copy", deepCopyOk, 1, debug.str());
    }
    score += deepCopyOk ? 1 : 0;

    // 4. Test assignment operator deep copy (using copyFrom)
    BattleHistory assignHistory;
    assignHistory.copyFrom(history);
    assignHistory.addLog("Assignment Log");
    bool assignCopyOk = (history.getLogCount() == 15 && assignHistory.getLogCount() == 16);
    {
        ostringstream debug;
        if (!assignCopyOk)
            debug << "Expected original count=15 and assign count=16, but got original count="
                << history.getLogCount() << " and assign count=" << assignHistory.getLogCount();
        printTestResult("Assignment Operator Deep Copy", assignCopyOk, 1, debug.str());
    }
    score += assignCopyOk ? 1 : 0;

    // 5. Test error handling: retrieving an invalid index should return an empty string (or appropriate error indicator)
    bool invalidIndexOk = (history.getLogAt(-1) == "" && history.getLogAt(100) == "");
    {
        ostringstream debug;
        if (history.getLogAt(-1) != "")
            debug << "Expected empty string for index -1, got '" << history.getLogAt(-1) << "'. ";
        if (history.getLogAt(100) != "")
            debug << "Expected empty string for index 100, got '" << history.getLogAt(100) << "'.";
        printTestResult("Invalid Log Index Handling", invalidIndexOk, 1, debug.str());
    }
    score += invalidIndexOk ? 1 : 0;

    cout << COLOR_BLUE << "\nTest 7 Total Score: " << score << "/5 points" << COLOR_RESET << endl;
    return 0;
}