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

void runTest(const std::string& testName, function<void(string, int&)> testFunc, int& marks);
void signalHandler(int signal);

// Test Cases - Prototypes

void testTeamClass(int& totalMarks, ostringstream& debug);
void testMatchClass(int& totalMarks, ostringstream& debug);
void testCricketDatabase(int& totalMarks, ostringstream& debug);

int main()
{
    int marks = 0;
    int bonusMarks = 0;

    ostringstream debug;

    cout << CYAN << "====== PA5 - Comprehensive Test ======" << RESET << endl;
    cout << RED << "Disclaimer: " << RESET;
    cout << "This test was made by a student and is NOT meant to be a guarentee for marks.\n";
    cout << "Only use this as a reference." << endl;
    cout << endl;

    signal(SIGSEGV, signalHandler);

    testTeamClass(marks, debug);

    testMatchClass(marks, debug);

    testCricketDatabase(marks, debug);


    cout << RESET;
    
    return 0;
}

void testTeamClass(int& totalMarks, ostringstream& debug)
{
    cout << CYAN << "Running Team class tests:\n" << endl;

    int marks = 0;

    // Team 1
    vector<string> playerNames = {"Alice", "Bob", "Charlie", "David"};

    Team warriors("Warriors", playerNames);

    // Test 1 - Team Name

    runTest("1 Team Name Retrieval", [&](string testName, int& childMarks)
    {
        string result = warriors.getName();
        debug << "Expected: \"Warriors\" - Got: ";
        debug << result;
        
        processTestResult(testName, debug.str(), result == "Warriors", childMarks, 1);
    }, marks);

    debug.str("");

    // Test 2 - Team Players

    runTest("2.1 Player Exists - Alice", [&](string testName, int& childMarks)
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult(testName, debug.str(), warriors.hasPlayer("Alice"), childMarks, 1);

    }, marks);
    
    debug.str("");

    runTest("2.2 Player Exists - Charlie", [&](string testName, int& childMarks)
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult(testName, debug.str(), warriors.hasPlayer("Charlie"), childMarks, 1);

    }, marks);

    debug.str("");

    runTest("2.3 Player Does Not Exist - Eve", [&](string testName, int& childMarks)
    {
        debug << "Expected: True - Got: " << warriors.hasPlayer("Alice");
        processTestResult(testName, debug.str(), !warriors.hasPlayer("Eve"), childMarks, 1);

    }, marks);

    debug.str("");

    runTest("2.4 Team Player Names Retrieval", [&](string testName, int& childMarks)
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
        
        processTestResult(testName, debug.str(), pass, childMarks, 2);

    }, marks);

    debug.str("");

    // Test 3 - Wins and Match Count

    runTest("3.1 Initial Wins and Matches", [&](string testName, int& childMarks)
    {
        int result1 = warriors.getWins();
        int result2 = warriors.getTotalMatches();
        debug << "Expected: Wins = 0 and Total Matches = 0 - Got: ";
        debug << "Wins = ";
        debug << warriors.getWins();
        debug << " and Total Matches = ";
        debug << warriors.getTotalMatches();
        
        processTestResult(testName, debug.str(), result1 == 0 && result2 == 0, childMarks, 1);

    }, marks);

    debug.str("");

    warriors.addMatch();
    warriors.addMatch();
    warriors.addWin();  // 1 win out of 2 matches

    runTest("3.2 Updated Wins and Matches", [&](string testName, int& childMarks)
    {
        int result1 = warriors.getWins();
        int result2 = warriors.getTotalMatches();
        debug << "Expected: Wins = 0 and Total Matches = 0 - Got: ";
        debug << "Wins = ";
        debug << warriors.getWins();
        debug << " and Total Matches = ";
        debug << warriors.getTotalMatches();
        
        processTestResult(testName, debug.str(), result1 == 1 && result2 == 2, childMarks, 1);

    }, marks);

    debug.str("");

    runTest("3.3 Win Percentage", [&](string testName, int& childMarks) 
    {
        debug << "Expected: Wins Percentage = 50 % - Got: ";
        debug << warriors.getWinPercentage() << " %";
 
        processTestResult(testName, debug.str(), warriors.getWinPercentage() == 50, childMarks, 1);

    }, marks);

    debug.str("");

    warriors.addMatch();
    warriors.addWin();

    runTest("3.4 Updated Wins Percentage", [&](string testName, int& childMarks)
    {
        debug << "Expected: Wins Percentage = 66 % - Got: ";
        debug << warriors.getWinPercentage() << " %";

        processTestResult(testName, debug.str(), warriors.getWinPercentage() == 66, childMarks, 1);

    }, marks);

    totalMarks += marks;    

    cout << "\nTeam Class tests completed. Take a short break :)" << endl;
    cout << CYAN << "Points: " << marks << " / 10\n" << RESET << endl;

}

void testMatchClass(int& totalMarks, ostringstream& debug)
{
    cout << CYAN << "Running Match Class Test:\n" << endl;

    Team tigers("Tigers", {"Alice", "Bob", "Charlie"});
    Team lions("Lions", {"David", "Eve", "Frank"});
    Match match(tigers, lions, 2024);

    int marks = 0;

    // Test 1 - Match Initialization

    runTest("1.1 Match Year", [&](string testName, int& childMarks)
    {
        debug << "Expected: 2024 - Got: ";
        debug << match.getYear();
        processTestResult(testName, debug.str(), match.getYear() == 2024, childMarks, 1);
    }, marks);

    debug.str("");

    runTest("1.2 Match PlayerStats Empty", [&](string testName, int& childMarks) 
    {
        debug << "Expected: True - Got: ";
        debug << match.getPlayerStats().empty();
        processTestResult(testName, debug.str(), match.getPlayerStats().empty(), childMarks, 1);
    }, marks);

    
    debug.str("");


    runTest("1.3 Match Winner Empty", [&](string testName, int& childMarks)
    {
        string result = match.getWinner();
        debug << "Expected: nullptr - Got: ";
        debug << result;
        processTestResult(testName, debug.str(), result == "", childMarks, 2);
    }, marks);

    debug.str("");

    // Test 2 - Adding Player Performances

    match.addPerformance("Alice", 50, 1);
    match.addPerformance("Bob", 30, 0);
    match.addPerformance("Charlie", 20, 2);

    match.addPerformance("David", 60, 0);
    match.addPerformance("Eve", 10, 1);
    match.addPerformance("Frank", 5, 3);

    runTest("2.1 Player Alice Performance", [&](string testName, int& childMarks)
    {
        auto result = match.getPlayerStats();
        debug << "Expected: Runs = 50 and Wickets = 1 - Got: Runs = ";
        debug << result["Alice"].first << " and Wickets = " << result["Alice"].second;
        processTestResult(testName, debug.str(), result["Alice"].first == 50 && result["Alice"].second == 1, childMarks, 1);

    }, marks);

    debug.str("");

    runTest("2.2 Player Frank Performance", [&](string testName, int& childMarks)
    {
        auto result = match.getPlayerStats();
        debug << "Expected: Runs = 5 and Wickets = 3 - Got: Runs = ";
        debug << result["Alice"].first << " and Wickets = " << result["Alice"].second;
        processTestResult(testName, debug.str(), result["Frank"].first == 5 && result["Frank"].second == 3, childMarks, 1);
        
    }, marks);

    debug.str("");

    runTest("2.3 Player Performances Exist", [&](string testName, int& childMarks)
    {
        auto result = match.getPlayerStats();
        debug << "Expected: 6 Performances - Got: ";
        debug << result.size() << " Performances";
        processTestResult(testName, debug.str(), result.size() == 6, childMarks, 1);
        
    }, marks);

    debug.str("");

    // Test 3 - The Winning Team

    match.setWinner();

    runTest("3.1 The Correct Winning Team", [&](string testName, int& childMarks)
    {
        string result = match.getWinner();
        debug << "Expected: Tigers - Got: ";
        debug << result;
        processTestResult(testName, debug.str(), result == "Tigers", childMarks, 1);
        
    }, marks);

    debug.str("");

    Match tieMatch(tigers, lions, 2025);
    tieMatch.addPerformance("Alice", 50, 0);
    tieMatch.addPerformance("Bob", 20, 1);
    tieMatch.addPerformance("Charlie", 30, 2);
    tieMatch.addPerformance("David", 60, 1);
    tieMatch.addPerformance("Eve", 30, 2);
    tieMatch.addPerformance("Frank", 10, 0);
    tieMatch.setWinner();

    runTest("3.2 The Tie Match", [&](string testName, int& childMarks)
    {
        string result = tieMatch.getWinner();
        debug << "Expected: Lions - Got: ";
        debug << result;
        processTestResult(testName, debug.str(), result == "Lions", childMarks, 2);
        
    }, marks);

    debug.str("");

    totalMarks += marks;

    cout << "\nMatch Class tests completed. Take a short break :).\n";
    cout << CYAN << "Points: " << marks << " / 10\n" << RESET << endl;

}

void testCricketDatabase(int& totalMarks, ostringstream& debug)
{
    cout << CYAN << "Running Cricket Database Test:\n" << endl;

    int marks = 0;

    vector<string> playerNames1 = {"Alice", "Bob"};
    vector<string> playerNames2 = {"Charlie", "David"};

    Team warriors("Warriors", playerNames1);
    Team strikers("Strikers", playerNames2);

    CricketDatabase db;
    CricketDatabase db2;

    // Test 1 - Adding Teams
    db.addTeam(warriors.getName(), warriors.getPlayers());
    db.addTeam(strikers.getName(), strikers.getPlayers());

    runTest("1 Team Added", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto teams = db.getTeams();
        auto result = teams["Warriors"];

        if (result.getName() != "Warriors")
        {
            pass = false;
        }
        

        debug << "Expected: Warriors - Got: ";
        debug << result.getName();
        processTestResult(testName, debug.str(), pass, childMarks, 1);

    }, marks);

    debug.str("");

    // Test 2 - Adding Match

    map<string, pair<int, int>> match1Stats =
    {
        {"Alice", {40, 2}}, {"Bob", {30, 0}},
        {"Charlie", {50, 1}}, {"David", {20, 2}}
    };

    db.addMatch("Warriors", "Strikers", 2024, match1Stats);

    runTest("2.1 Match Successfully Added", [&](string testName, int& childMarks)
    {
        bool operation = db.addMatch("Warriors", "Strikers", 2018, match1Stats);
        bool pass = true;

        if (!operation)
        {
            debug << "Expected: Funtion to return True - Got: Function returned Flase";
            processTestResult(testName, debug.str(), operation, childMarks, 1);
            return;
        }
        
        auto matches = db.getMatches();
        
        auto result = matches[1];

        pass = (result.getTeam1().getName() == "Warriors") && (result.getTeam2().getName() == "Strikers") && (result.getYear() == 2018) && (result.getWinner() == "Strikers");
        
        debug << "Expected: Team 1 = Warriors, Team 2 = Strikers, Year = 2018, Winner = Strikers - Got: Team 1 = ";
        debug << result.getTeam1().getName() << ", Team 2 = " << result.getTeam2().getName() << ", Year = " << result.getYear() << ", Winner = " << result.getWinner();

        processTestResult(testName, debug.str(), pass && operation, childMarks, 2);

    }, marks);

    debug.str("");

    runTest("2.2 Databases Teams Successfully Updated", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto teams = db.getTeams();

        pass = (teams["Warriors"].getWins() == 0) && (teams["Strikers"].getWins() == 1);

        debug << "Expected: Warriors Wins = 0, Strikers Wins = 1 - Got: ";
        debug << "Warriors Wins = " << teams["Warriors"].getWins() << ", Strikers Wins = " << teams["Strikers"].getWins();
        processTestResult(testName, debug.str(), pass, childMarks, 1);

    }, marks);

    debug.str("");

    runTest("2.3 Match Teams Successfully Updated", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto matches = db.getMatches();

        pass = (matches[0].getTeam1().getWins() == 0) && (matches[0].getTeam1().getWins() == 1);

        debug << "Expected: Warriors Wins = 0, Strikers Wins = 1 - Got: ";
        debug << "Warriors Wins = " << matches[0].getTeam1().getWins() << ", Strikers Wins = " << matches[0].getTeam1().getWins();
        processTestResult(testName, debug.str(), pass, childMarks, 1);

    }, marks);

    runTest("2.4 Performances Successfully Added", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto match = db.getMatches()[0];

        auto result = match.getPlayerStats();

        pass = (result == match1Stats);
        
        

        debug << "Expected: Warriors - Got: ";
        // debug << result.getName();
        processTestResult(testName, debug.str(), pass, childMarks, 1);

    }, marks);

    
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
            cout << YELLOW << "\tDebug -- " << debug << RESET << endl;

    }
}


bool isInText (const string& input, const string& passage)
{
    return false;
}


// Signal Handlers

void runTest(const std::string& testName, function<void(string, int&)> testFunc, int& marks)
{
    int pipeArr[2]; // pipe[0] = Read End, pipe[1] == Write End
    pipe(pipeArr);

    pid_t pid = fork();

    if (pid == 0)
    {
        // In child process: run the test

        close(pipeArr[0]);

        int childMarks = 0;
        testFunc(testName, childMarks);

        write(pipeArr[1], &childMarks, sizeof(int)); // Send to parent
        close(pipeArr[1]);

        exit(0); // Normal exit if no crash

    } 
    else
    {
        close(pipeArr[1]);

        // In parent process: wait and check status
        int status;

        waitpid(pid, &status, 0);

        int receivedMarks = 0;
        read(pipeArr[0], &receivedMarks, sizeof(int));
        close(pipeArr[0]);

        marks += receivedMarks; // Update parent's marks

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

void signalHandler(int signal)
{
    cerr << RED << "Critical Failure - Signal " << signal << " (Segmentation fault)" << endl;
    cerr << YELLOW << "Signal Caught - Program is Unstable: it may crash" << endl;
    cerr << YELLOW << "Attempting to Skip Test" << endl;
    
    std::signal(SIGSEGV, SIG_DFL);
    std::raise(SIGSEGV);
}

