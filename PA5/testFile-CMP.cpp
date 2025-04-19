#include <iostream>
#include <sstream>

#include <csignal>
#include <cstdlib>

#include <sys/wait.h>
#include <unistd.h>

#include <functional>


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

void runTest(const std::string& testName, std::function<void()> testFunc);
void signalHandler(int signal);

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

    signal(SIGSEGV, signalHandler);

    testTeamClass(marks, debug);

    testMatchClass(marks, debug);


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

    runTest("1 Team Name Retrieval", [&]()
    {
        string result = warriors.getName();
        debug << "Expected: \"Warriors\" - Got: ";
        debug << result;
        
        processTestResult("1 Team Name Retrieval", debug.str(), result == "Warriors", marks, 1);
    });

    debug.str("");

    // Test 2 - Team Players

    runTest("2.1 Player Exists - Alice", [&]()
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.1 Player Exists - Alice", debug.str(), warriors.hasPlayer("Alice"), marks, 1);

    });
    
    debug.str("");

    runTest("2.2 Player Exists - Charlie", [&]()
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.2 Player Exists - Charlie", debug.str(), warriors.hasPlayer("Charlie"), marks, 1);

    });

    debug.str("");

    runTest("2.3 Player Does Not Exist - Eve", [&]()
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult("2.3 Player Does Not Exist - Eve", debug.str(), !warriors.hasPlayer("Eve"), marks, 1);

    });

    debug.str("");

    runTest("2.4 Team Player Names Retrieval", [&]()
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

    });

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
        cout << "Error: Critical Failure - Re-Check your Getters function." << endl;
    }

    cout << "\nTeam Class tests completed. Take a short break :)\n" << endl;
    cout << CYAN << "Points: " << marks << " / 10" << RESET << endl;

}

void testMatchClass(int& marks, ostringstream& debug)
{
    Team tigers("Tigers", {"Alice", "Bob", "Charlie"});
    Team lions("Lions", {"David", "Eve", "Frank"});
    Match match(tigers, lions, 2024);

    // Test 1 - Match Initialization

    runTest("1.1 Match Year", [&]()
    {
        debug << "Expected: 2024 - Got: ";
        debug << match.getYear();
        processTestResult("1.1 Match Year", debug.str(), match.getYear() == 2024, marks, 1);
    });

    debug.str("");

    runTest("1.2 Match PlayerStats Empty", [&]() 
    {
        debug << "Expected: True - Got: ";
        debug << match.getPlayerStats().empty();
        processTestResult("1.2 Match PlayerStats Empty", debug.str(), match.getPlayerStats().empty(), marks, 1);
    });

    
    debug.str("");


    runTest("1.3 Match Winner Empty", [&]()
    {
        string result = match.getWinner();
        debug << "Expected: nullptr - Got: ";
        debug << result;
        processTestResult("1.3 Match Winner Empty", debug.str(), result == "", marks, 1);
    });

    debug.str("");
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


// Signal Handlers

void runTest(const std::string& testName, function<void()> testFunc)
{
    pid_t pid = fork();

    if (pid == 0)
    {
        // In child process: run the test
        testFunc();
        exit(0); // Normal exit if no crash

    } 
    else
    {
        // In parent process: wait and check status
        int status;

        waitpid(pid, &status, 0);

        if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            std::cout << YELLOW << "[SKIPPED] " << testName << " (crashed with signal " << sig << ")\n";
            
        }

        // TODO: Extra Logic if Need Be

        else if (WIFEXITED(status))
        {
            /* int exit_code = WEXITSTATUS(status);

            if (exit_code == 0)
            {
                std::cout << "[PASSED] " << testName << "\n";
            }
            else
            {
                std::cout << "[FAILED] " << testName << " (exit code " << exit_code << ")\n";
            } */

        }

        else
        {
            cout << RED << "[Warning] " << testName << " Test Ended Abnormally.\n";
        }

    }

}

// This Function is not used currently
void signalHandler(int signal)
{
    cerr << RED << "Critical Failure - Signal " << signal << " (Segmentation fault)" << endl;
    cerr << YELLOW << "Signal Caught - Program is Unstable: it may crash" << endl;
    cerr << YELLOW << "Attempting to Skip Test" << endl;
    
    std::signal(SIGSEGV, SIG_DFL);
    std::raise(SIGSEGV);
}

