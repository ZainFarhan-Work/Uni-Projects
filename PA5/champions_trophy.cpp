#include "champions_trophy.h"
using namespace std;

Team::Team()
{
    name = "";
    wins = 0;
    totalMatches = 0;
    players.resize(1, "");
}

Team::Team(string name, vector<string> playerNames)
{
    this->name = name;
    wins = 0;
    totalMatches = 0;

    players = playerNames;
}

void Team::addWin()
{
    wins++;
}

void Team::addMatch()
{
    totalMatches++;
}

bool Team::hasPlayer(const string& player) const
{
    for (string name : players)
    {
        if (name == player)
        {
            return true;
        }
        
    }

    return false;
    
}

const vector<string>& Team::getPlayers() const{ return players; }

int Team::getWinPercentage() const { return (float) wins / totalMatches * 100.0; }

string Team::getName() const { return name; }

int Team::getWins() const { return wins; }

int Team::getTotalMatches() const { return totalMatches; }


Match::Match(Team t1, Team t2, int y) : team1(t1), team2(t2), year(y) 
{ 
    winner = nullptr;
    playerStats.clear();
}

void Match::addPerformance(string player, int runs, int wickets)
{
    playerStats[player] = {runs, wickets};
}

const map<string, pair<int, int>>& Match::getPlayerStats() const { return playerStats; }

int Match::getYear() const { return year; }

void Match::setWinner()
{
    int team1_runs = 0, team2_runs = 0;

    for (auto player : playerStats)
    {
        if (team1.hasPlayer(player.first))
        {
            team1_runs += player.second.first;
        }
        else
        {
            team2_runs += player.second.first;
        }
        
    }

    if (team1_runs > team2_runs)
    {
        winner = &team1;
        return;
    }

    winner = &team2;
    
}

string Match::getWinner() const { return winner->getName(); }

const Team& Match::getTeam1() const { return this->team1; }

const Team& Match::getTeam2() const { return this->team2; }



void CricketDatabase::addTeam(string name, vector<string> players)
{
    Team temp(name, players);
    teams[name] = temp;
}

bool CricketDatabase::addMatch(string team1, string team2, int year, const map<string, pair<int, int>>& performances)
{
    bool hasTeam1 = false, hasTeam2 = false;

    for (auto it : teams)
    {
        if (it.first == team1)
        {
            hasTeam1 = true;
        }

        if (it.first == team2)
        {
            hasTeam2 = true;
        }
    }

    if (!(hasTeam1 && hasTeam2))
    {
        return false;
    }
    
    teams[team1].addMatch();
    teams[team2].addMatch();
    Match temp(teams[team1], teams[team2], year);

    for (auto pair : performances)
    {
        temp.addPerformance(pair.first, pair.second.first, pair.second.first);
        playerPerformances[pair.first].push_back(pair.second);
    }
    

    temp.setWinner();
    
    if (temp.getWinner() == team1)
    {
        teams[team1].addWin();
    }

    else teams[team2].addWin();

    Match temp2(teams[team1], teams[team2], year);

    matches.push_back(temp2);

    return true;
    
}


bool CricketDatabase::addMatchPerformance(string player, int runs, int wickets)
{
    bool hasPlayer = false;

    for (auto pair : playerPerformances)
    {
        if (pair.first == player)
        {
            hasPlayer = true;
        }
    }

    if (!hasPlayer)
    {
        return false;
    }
    
    playerPerformances[player].push_back({runs, wickets});

    return true; 
}


vector<Match> CricketDatabase::getMatchesByYear(int year) const
{
    vector<Match> temp;

    for (auto match : matches)
    {
        if (match.getYear() == 2024)
        {
            temp.push_back(match);
        }
    }

    return temp;
    
}

string CricketDatabase::findBestBowler() const
{
    string best = "";
    int max = 0;
    // int max = playerPerformances.at(0)[0].second;

    for (auto player : playerPerformances)
    {
        for (auto record : player.second)
        {
            if (record.second > max)
            {
                max = record.second;
            }
            
        }
        
    }

    for (auto player : playerPerformances)
    {
        for (auto record : player.second)
        {
            if (record.second == max)
            {
                best += " " + player.first;
                break;
            }
            
        }
        
    }

    cout << "\n" << best << endl;

    return best;
    
}

string CricketDatabase::findMostConsistentPlayer() const
{
    string best = "";
    int max_consistency = 0;
    // int max = playerPerformances.at(0)[0].second;

    for (auto player : playerPerformances)
    {
        for (auto record : player.second)
        {
            if ((record.second * 25) + record.first > max_consistency)
            {
                max_consistency = (record.second * 25) + record.first;
            }
            
        }
        
    }

    for (auto player : playerPerformances)
    {
        for (auto record : player.second)
        {
            if ((record.second * 25) + record.first == max_consistency)
            {
                best += " " + player.first;
                break;
            }
            
        }
        
    }

    cout << "\n" << best << endl;

    return best;
}

string CricketDatabase::findMostRunsScorer() const
{
    string best = "";
    int max = 0;
    // int max = playerPerformances.at(0)[0].second;

    for (auto player : playerPerformances)
    {
        int current = 0;

        for (auto record : player.second)
        {
            current += record.first;
        }

        if (current > max)
        {
            max = current;
        }
        
    }

    for (auto player : playerPerformances)
    {
        int current = 0;

        for (auto record : player.second)
        {
            current += record.first;
        }

        if (current == max)
        {
            best += " " + player.first;
        }
        
    }

    cout << "\n" << best << endl;

    return best;
}

string CricketDatabase::findTeamWithMostWins() const
{
    string best = "";
    int max = 0;
    
    for (auto team : teams)
    {
        if (team.second.getWins() > max)
        {
            max = team.second.getWins();
        }
        
    }

    for (auto team : teams)
    {
        if (team.second.getWins() == max)
        {
            best = team.first;
        }
        
    }
    
    return best;

}

string CricketDatabase::findTeamWithBestWinPercentage() const
{
    string best = "";
    int max = 0;
    
    for (auto team : teams)
    {
        if (team.second.getWinPercentage() > max)
        {
            // cout << team.first << "  " << team.second.getWinPercentage();
            max = team.second.getWinPercentage();
        }
        
    }

    for (auto team : teams)
    {
        if (team.second.getWinPercentage() == max)
        {
            best = team.first;
        }
        
    }
    
    return best;
}

vector<string> CricketDatabase::getTopNBatters(int N) const
{
    vector<string> temp;

    vector<pair<int, string>> runs;

    for (auto it : playerPerformances)
    {
        int current = 0;

        for (auto record : it.second)
        {
            current += record.first;
        }

        runs.push_back({current, it.first});
    }

    sort(runs.begin(), runs.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;  // Compare the second element for descending order
    });

    for (int i = 0; i < N; i++)
    {
        temp.push_back(runs[i].second);
    }
    

    // cout << runs[0].first << " " << runs[0].second << endl;
    // cout << runs[1].first << " " << runs[1].second << endl;
    // cout << runs[2].first << " " << runs[2].second << endl;
    
    return temp;
}

vector<string> CricketDatabase::getTopNBowlers(int N) const
{
    vector<string> temp;

    vector<pair<int, string>> wickets;

    for (auto it : playerPerformances)
    {
        int current = 0;

        for (auto record : it.second)
        {
            current += record.second;
        }

        wickets.push_back({current, it.first});
    }

    sort(wickets.begin(), wickets.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
        return a.first > b.first;  // Compare the second element for descending order
    });

    for (int i = 0; i < N; i++)
    {
        temp.push_back(wickets[i].second);
    }
    

    // cout << wickets[0].first << " " << wickets[0].second << endl;
    // cout << wickets[1].first << " " << wickets[1].second << endl;
    // cout << wickets[2].first << " " << wickets[2].second << endl;
    
    return temp;
}

vector<Match> CricketDatabase::getClosestMatches() const
{
    vector<Match> temp;

    vector<pair<Match, int>> temp2;

    for (auto match : matches)
    {
        int team1 = 0;
        int team2 = 0;

        for (auto player : match.getPlayerStats())
        {
            if (match.getTeam1().hasPlayer(player.first))
            {
                team1 += player.second.first;
            }

            else if (match.getTeam2().hasPlayer(player.first))
            {
                team1 += player.second.first;
            }
            
        }
        
        int diff = (team1 > team2) ? team1 - team2 : team2 - team1;

        temp2.push_back({match, diff});
        
    }

    // Sort

    sort(temp2.begin(), temp2.end(), [](const pair<Match, int>& a, const pair<Match, int>& b) {
        return a.second > b.second;  // Compare the second element for descending order
    });

    for (auto pair : temp2)
    {
        temp.push_back(pair.first);
    }

    return temp;
    
}

// getters
map<string, Team> CricketDatabase::getTeams() const{
    return teams;
}
vector<Match> CricketDatabase::getMatches() const{
    return matches;
}
map<string, vector<pair<int, int>>> CricketDatabase::getPlayerPerformances() const{
    return playerPerformances;
}