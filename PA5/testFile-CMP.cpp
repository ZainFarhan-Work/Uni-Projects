#include <iostream>
#include <sstream>

#include "champions_trophy.h"  // Assuming your Team class is in this file

using namespace std;

// ANSI color codes for terminal output
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Helper Functions - Prototypes

void processTestResult (const string& testName, const string& debug, bool passed, int& points, int testPoints = 1);
bool isInText (const string& input, const string& passage);

// Test Cases - Prototypes

void testTeamClass(int& marks, ostringstream& debug);
void testMatchClass(int& marks, ostringstream& debug);
void testCricketDatabase(int& marks, ostringstream& debug);

int main()
{
    int marks = 0;
    int bonusMarks;

    ostringstream debug;

    cout << CYAN << "====== PA5 - Comprehensive Test ======" << RESET << endl;
    cout << RED << "Disclaimer: " << RESET;
    cout << "This test was made by a student and is NOT meant to be a guarentee for marks.\n";
    cout << "Only use this as a reference." << endl;
    cout << endl;

    testTeamClass(marks, debug);


    cout << RESET;
    
    return 0;
}

void testTeamClass(int& marks, ostringstream& debug)
{
    cout << CYAN << "Running Team class tests:\n" << endl;

    // Team 1
    vector<string> playerNames = {"Alice", "Bob", "Charlie", "David"};

    Team warriors("Warriors", playerNames);

    // Test 1 - Team Name
    try
    {
        string result = warriors.getName();
        debug << "Expected: \"Warriors\" - Got: ";
        debug << result;
        
        processTestResult("1 Team Name Retrieval", debug.str(), result == "Warriors", marks, 1);

    }
    catch(...)
    {
        cout << "Error: Something Unexpected Happened - Re-Check your get name function." << endl;
    }

    debug.str("");

    // Test 2 - Team Players

    try
    {
        
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.1 Player Exists - Alice", debug.str(), warriors.hasPlayer("Alice"), marks, 1);
        debug.str("");

        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.2 Player Exists - Charlie", debug.str(), warriors.hasPlayer("Charlie"), marks, 1);
        debug.str("");

        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.3 Player Does Not Exist - Eve", debug.str(), !warriors.hasPlayer("Eve"), marks, 1);

    }
    catch(...)
    {
        cout << "Error: Something Unexpected Happened - Re-Check your Get Player function." << endl;
    }

    debug.str("");

    try
    {
        bool pass = true;
        string expected = "";
        string got = "";

        for (int i = 0; i < playerNames.size(); i++)
        {
            if (playerNames[i] != warriors.getPlayers()[i])
            {
                bool pass = false;
            }

            expected += playerNames[i] + " ";
            got += warriors.getPlayers()[i] + " ";
            
        }

        debug << "Expected: ";
        debug << expected;
        debug << "- Got: ";
        debug << got;
        
        processTestResult("2.4 Team Player Names Retrieval", debug.str(), pass, marks, 2);

    }
    catch(...)
    {
        cout << "Error: Something Unexpected Happened - Re-Check your Get Player function." << endl;
    }

    debug.str("");

    // Test 3 - Wins and Match Count

    try
    {
        int result1 = warriors.getWins();
        int result2 = warriors.getTotalMatches();
        debug << "Expected: Wins = 0 and Total Matches = 0 - Got: ";
        debug << "Wins = ";
        debug << warriors.getWins();
        debug << " and Total Matches = ";
        debug << warriors.getTotalMatches();
        
        processTestResult("3.1 Initial Wins and Matches", debug.str(), result1 == 0 && result2 == 0, marks, 1);

        debug.str("");

        warriors.addMatch();
        warriors.addMatch();
        warriors.addWin();  // 1 win out of 2 matches

        result1 = warriors.getWins();
        result2 = warriors.getTotalMatches();
        debug << "Expected: Wins = 0 and Total Matches = 0 - Got: ";
        debug << "Wins = ";
        debug << warriors.getWins();
        debug << " and Total Matches = ";
        debug << warriors.getTotalMatches();
        
        processTestResult("3.2 Updated Wins and Matches", debug.str(), result1 == 1 && result2 == 2, marks, 1);

        debug.str("");

        debug << "Expected: Wins Percentage = 50 % - Got: ";
        debug << warriors.getWinPercentage() << " %";

        processTestResult("3.3 Win Percentage", debug.str(), warriors.getWinPercentage() == 50, marks, 1);

        warriors.addMatch();
        warriors.addWin();

        debug.str("");

        debug << "Expected: Wins Percentage = 66 % - Got: ";
        debug << warriors.getWinPercentage() << " %";

        processTestResult("3.3 Updated Wins and Matches", debug.str(), warriors.getWinPercentage() == 66, marks, 1);

    }
    catch(...)
    {
        cout << "Error: Something Unexpected Happened - Re-Check your get name function." << endl;
    }

    cout << "\nTeam Class tests completed. Take a short break :)\n";
    cout << CYAN << "Points: " << marks << " / 10" << RESET << endl;

}


// Helper Functions

void processTestResult (const string& testName, const string& debug, bool passed, int& points, int testPoints)
{
    if (passed)
    {
        cout << GREEN << "[PASSED] " << testName << " (" << testPoints << " points)" << RESET << endl;
        points += testPoints;
    }
    else
    {
        cout << RED << "[FAILED] " << testName << " (0 points)" << RESET << endl;

        if (!debug.empty())
            cout << YELLOW << "       Debug: " << debug << RESET << endl;

    }
}


bool isInText (const string& input, const string& passage)
{
    return false;
}

