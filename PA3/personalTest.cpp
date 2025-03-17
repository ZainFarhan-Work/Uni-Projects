#include <iostream>
#include <sstream>
#include "./src/Trainer.cpp"
#include "./src/Shop.cpp"
#include "./src/Gym.cpp"
#include "./src/Armor.cpp"
#include "./src/Move.cpp"
#include "./src/Pokemon.cpp"
#include "./src/Potion.cpp"
#include "./src/BattleHistory.cpp"
#include "./src/Battle.cpp"
#include "./src/GameState.cpp"

using namespace std;

int main()
{
    Battle::deterministic = false;

    BattleHistory gameLogs;

    Trainer* ash = new Trainer("Ashley"); // Player
    Trainer* gymLeader = new Trainer("Brock");

    Gym* gym = new Gym(gymLeader, "Brock Badge", 2);
    
    Shop* shop = nullptr;
    
    GameState game(ash, gym, shop);
    
    Armor* basic = new Armor("basic", 7, 40);

    Pokemon* picka = new Pokemon;
    Pokemon* onix = new Pokemon("Onix", "Earth", 102);

    picka->equipArmor(*basic);

    ash->addPokemon(picka);

    gymLeader->addPokemon(onix);

    gym->addGymPokemon(onix);

    gym->battle(ash);

    cout << "\n";

    cout << gym->getGymHistory().getAllLogs() << endl;

    return 0;
}