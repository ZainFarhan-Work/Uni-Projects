#ifndef BATTLEHISTORY_HPP
#define BATTLEHISTORY_HPP

#include <string>
using namespace std;

class BattleHistory
{
private:
    string *logs;
    int count;
    int capacity;

    void expandLogs();

public:
    // Constructors
    BattleHistory();

    // Copy constructor, assignment operator, and destructor
    BattleHistory(const BattleHistory &other);
    ~BattleHistory();


    // Assignment Function
    void copyFrom(const BattleHistory &other);
    
    // Log management
    void addLog(const string &entry);
    string getLogAt(int index) const;
    int getLogCount() const;
    void clearLogs();

    // Retrieve all logs as a single string
    string getAllLogs() const;
};

#endif