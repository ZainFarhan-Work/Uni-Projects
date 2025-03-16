//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/BattleHistory.cpp
#include "../include/BattleHistory.hpp"
#include <iostream>

// Private expansion
void BattleHistory::expandLogs()
{
    // Resize Array
    string* temp = logs;

    logs = new string[capacity * 2];

    // Copying data from Old Array into New

    for (int i = 0; i < count - 1; i++)
    {
        logs[i] = temp[i];
    }

    // Deleting Old Array
    delete[] temp;

    capacity *= 2;

    return;

}

// Constructor
BattleHistory::BattleHistory() 
{
    count = 0;
    capacity = 1;
    logs = new string[1];

}

// Copy constructor
BattleHistory::BattleHistory(const BattleHistory &other) 
{
    count = other.count;
    capacity = other.capacity;

    logs = new string[other.capacity];

    for (int i = 0; i < other.count; i++)
    {
        logs[i] = other.logs[i];
    }
    
}

// Destructor
BattleHistory::~BattleHistory()
{
    delete[] logs;
}

// Log management
void BattleHistory::addLog(const string &entry)
{
    if (++count > capacity)
    {
        expandLogs();
    }

    logs[count - 1] = entry;

}

string BattleHistory::getLogAt(int index) const
{
    if (index < 0 || index >= count)
    {
        return "";
    }
    
    return logs[index];
}

int BattleHistory::getLogCount() const
{
    return count;
}

void BattleHistory::clearLogs()
{
    delete[] logs;

    count = 0;
    capacity = 1;

    logs = new string[1];
}

//This function will be used to return all logs in a single "multiline" string
string BattleHistory::getAllLogs() const
{
    string battleHistory = "";

    for (int i = 0; i < count; i++)
    {
        battleHistory += logs[i] + "\n";
    }
    
    return battleHistory;
}

void BattleHistory::copyFrom(const BattleHistory &other)
{
    count = other.count;
    capacity = other.capacity;

    delete[] logs;

    logs = new string[other.capacity];

    for (int i = 0; i < other.count; i++)
    {
        logs[i] = other.logs[i];
    }
    

}