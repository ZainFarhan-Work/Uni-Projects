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
void bonusTests(int& totalMarks, ostringstream& debug);

int main()
{
    int marks = 0;
    int bonusMarks = 0;

    ostringstream debug;

    cout << CYAN << "========== PA5 - Comprehensive Test ==========" << RESET << endl;
    cout << RED << "Disclaimer: " << RESET;
    cout << "This test was made by a student and is NOT meant to be a guarentee for marks.\n";
    cout << "Only use this as a reference." << endl;
    cout << endl;

    signal(SIGSEGV, signalHandler);

    testTeamClass(marks, debug);

    testMatchClass(marks, debug);

    testCricketDatabase(marks, debug);

    bonusTests(bonusMarks, debug);

    cout << CYAN << "======== Marks ========" << endl;
    cout << endl;

    cout << "Base Marks: " << marks << "/70" << endl;
    cout << "Bonus Marks: " << bonusMarks << "/30" << endl;
    cout << endl;
    cout << "Total Marks: " << marks + bonusMarks << "/100" << endl;

    cout << endl;

    cout << CYAN << "======== Grade ========" << endl;
    cout << endl;


    if (marks + bonusMarks == 100) // == 100
    {
        cout << GREEN << "\t ~Perfect~ \t" << endl;
    }
    else if (marks == 70) // == 70
    {
        cout << GREEN << "\t *Great* \t" << endl;
    }
    else if (marks + bonusMarks >= 60) // >= 60
    {
        cout << YELLOW << "\t Good \t" << endl;
    }
    else
    {
        cout << RED << "\t Bad \t" << endl;
        cout << YELLOW << "Note: Skill Issue" << endl;
    }

    cout << RESET << endl;
    
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
        debug << "Expected: Wins = 1 and Total Matches = 2 - Got: ";
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
    cout << CYAN << "Marks: " << marks << " / 10\n" << RESET << endl;

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

    cout << "\nMatch Class tests completed. Take a short break :)\n";
    cout << CYAN << "Marks: " << marks << " / 10\n" << RESET << endl;

}

void testCricketDatabase(int& totalMarks, ostringstream& debug)
{
    cout << CYAN << "Running Cricket Database Test:\n" << endl;

    int marks = 0;

    vector<string> playerNames1 = {"Alice", "Bob"};
    vector<string> playerNames2 = {"Charlie", "David"};
    vector<string> playerNames3 = {"Yuki", "Zack"};

    Team warriors("Warriors", playerNames1);
    Team strikers("Strikers", playerNames2);
    Team falcon("Falcon", playerNames3);

    CricketDatabase db;
    CricketDatabase db2;

    // Test 1 - Adding Teams
    db.addTeam(warriors.getName(), warriors.getPlayers());
    db.addTeam(strikers.getName(), strikers.getPlayers());
    db.addTeam(falcon.getName(), falcon.getPlayers());

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
        {"Alice", {40, 1}}, {"Bob", {30, 0}},
        {"Charlie", {50, 1}}, {"David", {20, 3}}
    };

    map<string, pair<int, int>> match2Stats =
    {
        {"Alice", {20, 1}}, {"Bob", {0, 1}},
        {"Charlie", {20, 1}}, {"David", {20, 1}}
    };

    map<string, pair<int, int>> match3Stats =
    {
        {"Yuki", {100, 2}}, {"Zack", {50, 1}},
        {"Charlie", {20, 1}}, {"David", {0, 1}}
    };

    db.addMatch("Warriors", "Strikers", 2024, match1Stats);
    db.addMatch("Warriors", "Strikers", 2025, match2Stats);
    db.addMatch("Falcon", "Strikers", 2024, match3Stats);

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
        
        auto result = matches[3];

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

        pass = (teams["Warriors"].getWins() == 0) && (teams["Strikers"].getWins() == 2);

        debug << "Expected: Warriors Wins = 0, Strikers Wins = 2 - Got: ";
        debug << "Warriors Wins = " << teams["Warriors"].getWins() << ", Strikers Wins = " << teams["Strikers"].getWins();
        processTestResult(testName, debug.str(), pass, childMarks, 2);

    }, marks);

    debug.str("");

    runTest("2.3 Match Teams Successfully Updated", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto matches = db.getMatches();

        pass = (matches[0].getTeam1().getWins() == 0) && (matches[0].getTeam1().getWins() == 2);

        debug << "Expected: Warriors Wins = 0, Strikers Wins = 2 - Got: ";
        debug << "Warriors Wins = " << matches[0].getTeam1().getWins() << ", Strikers Wins = " << matches[0].getTeam1().getWins();
        processTestResult(testName, debug.str(), pass, childMarks, 4);

    }, marks);

    debug.str("");

    runTest("2.4 Performances Successfully Added", [&](string testName, int& childMarks)
    {
        bool pass = true;
        auto match = db.getMatches()[0];

        auto result = match.getPlayerStats();
        
        debug << "Expected:\n";
        for (auto pair : match1Stats)
        {
            debug << pair.first << ": runs = " << pair.second.first << " wickets = " << pair.second.second;
            debug << endl;
        }

        debug << "\nGot -\n";
        
        for (auto pair : result)
        {
            debug << pair.first << ": runs = " << pair.second.first << " wickets = " << pair.second.second;
            debug << endl;
        }

        pass = (result == match1Stats);

        processTestResult(testName, debug.str(), pass, childMarks, 2);

    }, marks);

    debug.str("");

    // Test 3 - Adding Performances

    db.addMatchPerformance("Alice", 100, 2);
    db.addMatchPerformance("David", 0, 2);

    db.addMatchPerformance("Alice", 60, 1);
    db.addMatchPerformance("David", 15, 1);

    runTest("3.1 Performances Successfully Updated", [&](string testName, int& childMarks)
    {
        bool operation = db.addMatchPerformance("Alice", 50, 1);

        if (!operation)
        {
            debug << "Expected: Function to return True - Got: Function returned False";
            processTestResult(testName, debug.str(), operation, childMarks, 2);
        }
        

        bool pass = true;
        auto result = db.getPlayerPerformances();

        vector<pair<int, int>> aliceResult = {{40, 1}, {20, 1}, {100, 2}, {60, 1}, {50, 1}};
        vector<pair<int, int>> davideResult = {{20, 3}, {20, 1}, {0, 1}, {0, 2}, {15, 1}};

        debug << "\nExpected: Alice = {40, 1} {20, 1} {100, 2} {60, 1} {50, 1} - Got: Alice = ";

        int count = 0;
        for (auto alice : result["Alice"])
        {
            if (alice.first != aliceResult[count].first || alice.second != aliceResult[count].second)
            {
                pass = false;
            }

            debug << "{" << alice.first << ", " << alice.second << "} ";
            count++;
            
        }

        debug << "\nExpected: David = {20, 3} {20, 1} {0, 1} {0, 2} {15, 1} - Got: ";

        count = 0;
        for (auto david : result.at("David"))
        {
            if (david.first != davideResult[count].first || david.second != davideResult[count].second)
            {
                pass = false;
            }

            debug << "{" << david.first << ", " << david.second << "} ";
            count++;
            
        }
        
        processTestResult(testName, debug.str(), pass, childMarks, 2);

    }, marks);

    debug.str("");

    runTest("3.2 Adding Non-Existent Performance", [&](string testName, int& childMarks)
    {
        bool operation = db.addMatchPerformance("Eve", 50, 1);
        auto stats = db.getPlayerPerformances();

        if (operation)
        {
            debug << "Expected: Function to return Flase - Got: Function returned True";
            processTestResult(testName, debug.str(), operation, childMarks, 1);
        }

        if (stats.find("Eve") != stats.end())
        {
            debug << "Expected: Eve Not Found in Stats - Got: Eve was Found in Stats";
            operation = true;
        }
        
        
        processTestResult(testName, debug.str(), !operation, childMarks, 1);

    }, marks);

    debug.str("");

    // Test 4 - Getting Data

    runTest("4.1 Getting Match By Year", [&](string testName, int& childMarks)
    {
        auto result = db.getMatchesByYear(2024);
        auto stats = db.getPlayerPerformances();

        if (result.empty())
        {
            debug << "Function Returned Empty Vector";
            processTestResult(testName, debug.str(), false, childMarks, 2);
            return;
        }

        for (auto match : result)
        {
            if (match.getYear() != 2024)
            {
                debug << "Expected: 2024 - Got: " << match.getYear();
                processTestResult(testName, debug.str(), false, childMarks, 2);
                return;
            }
            
        }
        
        processTestResult(testName, debug.str(), true, childMarks, 2);

    }, marks);

    debug.str("");

    // Prints Out DataBase Data : Uncomment for Debugging

    // cout << "----\n";
    // auto perf = db.getPlayerPerformances();
    // std::cout << "Before test:\n";
    // for (auto& [name, matches] : perf) {
    //     std::cout << name << ": ";
    //     for (auto& [runs, wkts] : matches)
    //         std::cout << "{" << runs << ", " << wkts << "} ";
    //     std::cout << "\n";
    // }
    // cout << "----\n";

    // auto teams = db.getTeams();
    // std::cout << "Before test:\n";
    // for (auto& [name, team] : teams)
    // {
    //     std::cout << name << ": ";
    //     std::cout << "{" << team.getWins() << ", " << team.getWinPercentage() << "% } ";
    //     std::cout << "\n";
    // }
    // cout << "----\n";
    
    runTest("4.2 Retrieving Best Bowler", [&](string testName, int& childMarks)
    {
        string result = db.findBestBowler();
        
        debug << "Expected: David - Got: " << result;

        processTestResult(testName, debug.str(), isInText("David", result), childMarks, 2);

    }, marks);

    debug.str("");

    runTest("4.3 Retrieving Most Runs Scorer", [&](string testName, int& childMarks)
    {
        string result = db.findMostRunsScorer();
        
        debug << "Expected: Alice - Got: " << result;

        processTestResult(testName, debug.str(), isInText("Alice", result), childMarks, 2);

    }, marks);

    debug.str("");

    runTest("4.4 Retrieving Most Consistent Player", [&](string testName, int& childMarks)
    {
        string result = db.findMostConsistentPlayer();
        
        debug << "Expected: Alice - Got: " << result;

        processTestResult(testName, debug.str(), isInText("Alice", result), childMarks, 2);

    }, marks);

    debug.str("");

    runTest("4.5 Retrieving Team with Most Wins", [&](string testName, int& childMarks)
    {
        string result = db.findTeamWithMostWins();
        
        debug << "Expected: Strikers - Got: " << result;

        processTestResult(testName, debug.str(), isInText("Strikers", result), childMarks, 2);

    }, marks);

    debug.str("");

    runTest("4.6 Retrieving Team with Best Win Percentage", [&](string testName, int& childMarks)
    {
        string result = db.findTeamWithBestWinPercentage();
        
        debug << "Expected: Falcon - Got: " << result;

        processTestResult(testName, debug.str(), isInText("Falcon", result), childMarks, 2);

    }, marks);

    debug.str("");

    // Test 5 - Getting Data in Lists

    runTest("5.1 Retrieving Top 3 Batters", [&](string testName, int& childMarks)
    {
        auto result = db.getTopNBatters(3);
        bool pass = (result[0] == "Alice") && (result[1] == "Yuki") && (result[2] == "Charlie");
        
        debug << "Expected: Alice Yuki Charlie - Got: ";
        debug << result[0] << " " << result[1] << " " << result[2];

        processTestResult(testName, debug.str(), pass, childMarks, 8);

    }, marks);

    debug.str("");

    runTest("5.2 Retrieving Top 3 Bowlers", [&](string testName, int& childMarks)
    {
        auto result = db.getTopNBowlers(3);
        bool pass = (result[0] == "David") && (result[1] == "Alice") && (result[2] == "Charlie");
        
        debug << "Expected: David Alice Charlie - Got: ";
        debug << result[0] << " " << result[1] << " " << result[2];

        processTestResult(testName, debug.str(), pass, childMarks, 8);

    }, marks);

    debug.str("");

    runTest("5.3 Retrieving Closest Matches", [&](string testName, int& childMarks)
    {
        auto result = db.getClosestMatches();
        bool pass = true;
        
        debug << "\nExpected: Warriors vs Strikers 2024, Warriors vs Strikers 2025, Falcon vs Strikers 2024\n";
        debug << "Got: ";

        for (int i = 0; i < 3; i++)
        {
            debug << result[i].getTeam1().getName() << " vs " <<  result[i].getTeam2().getName() << " " << result[i].getYear();
            debug << " ";
        }

        pass = (result[0].getTeam1().getName() == "Warriors");
        pass = pass && (result[0].getTeam2().getName() == "Strikers") && (result[0].getYear() == 2024);

        pass = pass && (result[1].getTeam1().getName() == "Warriors");
        pass = pass && (result[1].getTeam2().getName() == "Strikers") && (result[1].getYear() == 2025);
                
        pass = pass && (result[2].getTeam1().getName() == "Falcon");
        pass = pass && (result[2].getTeam2().getName() == "Strikers") && (result[2].getYear() == 2024);

        processTestResult(testName, debug.str(), pass, childMarks, 8);

    }, marks);

    debug.str("");

    totalMarks += marks;

    cout << "\nCricket Database Class tests completed. Take a short break :)\n";
    cout << CYAN << "Marks: " << marks << " / 50\n" << RESET << endl;
}

void bonusTests(int& totalMarks, ostringstream& debug)
{
    cout << CYAN << "Running Team class tests:\n" << endl;

    int marks = 0;

    vector<string> playerNames1 = {"Alice", "Bob"};
    vector<string> playerNames2 = {"Charlie", "David"};
    vector<string> playerNames3 = {"Yuki", "Zack"};

    Team warriors("Warriors", playerNames1);
    Team strikers("Strikers", playerNames2);
    Team falcon("Falcon", playerNames3);

    CricketDatabase db;
    CricketDatabase db2;

    db.addTeam(warriors.getName(), warriors.getPlayers());
    db.addTeam(strikers.getName(), strikers.getPlayers());
    db.addTeam(falcon.getName(), falcon.getPlayers());

    map<string, pair<int, int>> match1Stats =
    {
        {"Alice", {60, 4}}, {"Bob", {30, 0}},
        {"Charlie", {50, 0}}, {"David", {60, 4}}
    };

    map<string, pair<int, int>> match2Stats =
    {
        {"Alice", {100, 2}}, {"Bob", {0, 1}},
        {"Charlie", {20, 1}}, {"David", {100, 2}}
    };

    map<string, pair<int, int>> match3Stats =
    {
        {"Yuki", {100, 2}}, {"Zack", {50, 1}},
        {"Charlie", {20, 1}}, {"David", {0, 0}}
    };

    db.addMatch("Warriors", "Strikers", 2024, match1Stats);
    db.addMatch("Warriors", "Strikers", 2025, match2Stats);
    db.addMatch("Falcon", "Strikers", 2024, match3Stats);
    

    // Test 1 - Invalid Inputs
    runTest("1 Invalid Win Count", [&](string testName, int& childMarks)
    {
        warriors.addMatch();
        warriors.addWin();
        warriors.addWin();

        int result1 = warriors.getWins();
        int result2 = warriors.getTotalMatches();
        debug << "Expected: Wins = 1 and Total Matches = 1 - Got: ";
        debug << "Wins = ";
        debug << warriors.getWins();
        debug << " and Total Matches = ";
        debug << warriors.getTotalMatches();
        
        processTestResult(testName, debug.str(), result1 == 1 && result2 == 1, childMarks, 2);

    }, marks);

    debug.str("");

    // Test 2 - Ties
    runTest("2.1 Retrieving Best Bowler (Ties)", [&](string testName, int& childMarks)
    {
        string result = db.findBestBowler();
        
        debug << "Expected: [Alice, David] - Got: " << result;
        debug << "\nNote:The Test Cases don't check for String Formatting";

        processTestResult(testName, debug.str(), isInText("Alice", result) && isInText("David", result), childMarks, 7);

    }, marks);

    debug.str("");

    runTest("2.2 Retrieving Best Batter (Ties)", [&](string testName, int& childMarks)
    {
        string result = db.findMostRunsScorer();
        
        debug << "Expected: [Alice, David] - Got: " << result;
        debug << "\nNote:The Test Cases don't check for String Formatting";

        processTestResult(testName, debug.str(), isInText("Alice", result) && isInText("David", result), childMarks, 7);

    }, marks);

    debug.str("");

    runTest("2.3 Retrieving Most Consistent Player (Ties)", [&](string testName, int& childMarks)
    {
        string result = db.findMostConsistentPlayer();
        
        debug << "Expected: [Alice, David] - Got: " << result;
        debug << "\nNote:The Test Cases don't check for String Formatting";

        processTestResult(testName, debug.str(), isInText("Alice", result) && isInText("David", result), childMarks, 7);

    }, marks);

    debug.str("");

    runTest("2.4 Retrieving Team with Most Wins (Ties)", [&](string testName, int& childMarks)
    {
        string result = db.findTeamWithMostWins();
        
        debug << "Expected: [Falcon, Strikers] - Got: " << result;
        debug << "\nNote:The Test Cases don't check for String Formatting";

        processTestResult(testName, debug.str(), isInText("Strikers", result) && isInText("Falcon", result), childMarks, 7);

    }, marks);

    debug.str("");

    totalMarks += marks;

    cout << "\nAll tests completed. Take a short break :)\n";
    cout << CYAN << "Marks: " << marks << " / 30\n" << RESET << endl;
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
        cout << RED << "[FAILED] " << testName << " (0/" << testPoints << " points)" << RESET << endl;

        if (!debug.empty())
            cout << YELLOW << "\tDebug -- " << debug << RESET << endl;

    }
}


bool isInText (const string& input, const string& passage)
{
    return (passage.find(input) != string::npos);
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

