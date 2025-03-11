// Test.cpp - Auto-compiling test runner for all tests in subdirectory "tests"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
using namespace std;

#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_RESET "\033[0m"

int interface()
{
    const char *parts[] = {"Exit", "Test1: Move, Armor, and Potion Classes", "Test2: Pokemon Class", "Test3: Trainer, party and potion", "Test4: Shop functionality", "Test5: Gym class functionality", "Test6: GameState functionality", "Test7: BattleHistory Class"};
    const int marks[] = {0, 12, 18, 20, 14, 18, 13, 5}; // Updated marks distribution
    int input;

    cout << COLOR_YELLOW << string(90, '-') << endl;
    cout << left << setw(10) << "Index" << setw(40) << "Test Category" << setw(10) << "Marks" << endl;
    cout << string(90, '-') << COLOR_RESET << endl;
    for (size_t i = 0; i < sizeof(parts) / sizeof(parts[0]); ++i)
        cout << left << setw(10) << i << setw(40) << parts[i] << setw(10) << marks[i] << endl;
    cout << COLOR_YELLOW << string(90, '-') << COLOR_RESET << endl;
    cout << COLOR_BLUE << "Enter the index of the test you want to run: " << COLOR_RESET;
    cin >> input;
    return input;
}

void start()
{
    int flag = 1;
    while (flag)
    {
        switch (interface())
        {
        case 0:
            cout << COLOR_BLUE << "Exiting...\n"
                 << COLOR_RESET;
            flag = 0;
            break;
        case 1:
            cout << COLOR_BLUE << "Compiling test1..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test1.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp \
                    -o tests/test1");
            cout << COLOR_BLUE << "Running test1..." << COLOR_RESET << endl;
            system("./tests/test1");
            break;
        case 2:
            cout << COLOR_BLUE << "Compiling test2..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test2.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp src/Pokemon.cpp \
                    -o tests/test2");
            cout << COLOR_BLUE << "Running test2..." << COLOR_RESET << endl;
            system("./tests/test2");
            break;
        case 3:
            cout << COLOR_BLUE << "Compiling test3..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test3.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp src/Pokemon.cpp src/Trainer.cpp \
                    -o tests/test3");
            cout << COLOR_BLUE << "Running test3..." << COLOR_RESET << endl;
            system("./tests/test3");
            break;
        case 4:
            cout << COLOR_BLUE << "Compiling test4..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test4.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp src/Pokemon.cpp src/Trainer.cpp src/Shop.cpp \
                    -o tests/test4");
            cout << COLOR_BLUE << "Running test4..." << COLOR_RESET << endl;
            system("./tests/test4");
            break;
        case 5:
            cout << COLOR_BLUE << "Compiling test5..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test5.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp src/Pokemon.cpp src/Trainer.cpp \
                    src/Shop.cpp src/Gym.cpp src/Battle.cpp src/BattleHistory.cpp \
                    -o tests/test5");
            cout << COLOR_BLUE << "Running test5..." << COLOR_RESET << endl;
            system("./tests/test5");
            break;
        case 6:
            cout << COLOR_BLUE << "Compiling test6..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test6.cpp \
                    src/Move.cpp src/Armor.cpp src/Potion.cpp src/Pokemon.cpp src/Trainer.cpp \
                    src/Shop.cpp src/Gym.cpp src/Battle.cpp src/BattleHistory.cpp src/GameState.cpp \
                    -o tests/test6");
            cout << COLOR_BLUE << "Running test6..." << COLOR_RESET << endl;
            system("./tests/test6");
            break;
            break;
        case 7:
            cout << COLOR_BLUE << "Compiling test7..." << COLOR_RESET << endl;
            system("g++ -std=c++11 -Iinclude -g tests/test7.cpp \
                    src/BattleHistory.cpp \
                    -o tests/test7");
            cout << COLOR_BLUE << "Running test7..." << COLOR_RESET << endl;
            system("./tests/test7");
            break;
        default:
            cout << COLOR_RED << "No such test exists. Please try again.\n"
                 << COLOR_RESET;
            break;
        }
    }
}

int main()
{
    start();
    return 0;
}