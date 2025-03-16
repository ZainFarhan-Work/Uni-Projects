#include <iostream>
#include <sstream>
#include "./src/Trainer.cpp"
#include "./src/Armor.cpp"
#include "./src/Move.cpp"
#include "./src/Pokemon.cpp"
#include "./src/Potion.cpp"
#include "./src/BattleHistory.cpp"
#include "./src/Battle.cpp"

using namespace std;

int main()
{
    Pokemon p("Charizard", "Fire", 150);
    Pokemon p1;

    Move m1("Flamethrower", 90, 85, 15);
    Move m2("Dragon Claw", 80, 90, 20);

    p.addMove(m1);
    p.addMove(m2);

    Battle battle(p, p1);

    battle.simulateFullBattle();

    BattleHistory history = battle.getBattleHistory();

    string prt = history.getAllLogs();

    cout << prt << endl;

    return 0;
}