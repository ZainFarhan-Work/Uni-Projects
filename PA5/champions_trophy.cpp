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

void Team::addWin(){
}

void Team::addMatch(){
}

bool Team::hasPlayer(const string& player) const {
}

const vector<string>& Team::getPlayers() const { 
}

int Team::getWinPercentage() const {
}

string Team::getName() const {
}

int Team::getWins() const {
}

int Team::getTotalMatches() const {
}

Match::Match(Team t1, Team t2, int y){ }

void Match::addPerformance(string player, int runs, int wickets){
}

const map<string, pair<int, int>>& Match::getPlayerStats() const {
}

int Match::getYear() const {
}

void Match::setWinner(){
}

string Match::getWinner() const {
}

const Team& Match::getTeam1() const {
}

const Team& Match::getTeam2() const {
}

void CricketDatabase::addTeam(string name, vector<string> players){
}

bool CricketDatabase::addMatch(string team1, string team2, int year, const map<string, pair<int, int>>& performances) {
}


bool CricketDatabase::addMatchPerformance(string player, int runs, int wickets) { 
}


vector<Match> CricketDatabase::getMatchesByYear(int year) const {
}

string CricketDatabase::findBestBowler() const {
}

string CricketDatabase::findMostConsistentPlayer() const {
}

string CricketDatabase::findMostRunsScorer() const {
}

string CricketDatabase::findTeamWithMostWins() const { 
}

string CricketDatabase::findTeamWithBestWinPercentage() const {
}

vector<string> CricketDatabase::getTopNBatters(int N) const {
}

vector<string> CricketDatabase::getTopNBowlers(int N) const {
}

vector<Match> CricketDatabase::getClosestMatches() const {
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