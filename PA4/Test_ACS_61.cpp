/* 
FOR TESTING PURPOSES ONLY.
DO NOT EDIT.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip> 
#include <cstdlib>
#include <thread>

using namespace std;

int interface() 
{
    const char* parts[] = {"Exit", "Aircraft Class", "CombatAircraft Class", "StealthAircraft Class", "AbductorCraft Class", "GuardianCraft Class", "AircraftStatus Operator", "Aircraft Operators", "CombatAircraft Operators", "StealthAircraft Operators", "AbductorCraft Operators", "GuardianCraft Operators", "Test All Parts"};
    const double marks[] = {0, 10, 10, 10, 10, 10, 2, 12, 9, 5, 15, 7, 100};
    int input;

    cout << string(90, '-') << endl;
    cout << left << setw(30) << "Index" << setw(50) << "Part" << setw(10) << "Marks" << endl;
    cout << string(90, '-') << endl;

    // Iterate and print each part with its index and marks
    for (size_t i = 0; i < sizeof(parts) / sizeof(parts[0]); ++i) 
        cout << left << setw(30) << i << setw(50) << parts[i] << setw(10) << marks[i] << endl;
    cout << string(90, '-') << endl;

    cout << "Enter the index of the test that you want to run: ";
    cin >> input;

    return input;
}

void start() 
{
    chdir("Test");
    int flag = 1;

    while (flag)
    {
        switch (interface()) 
        {
        case 0:
            cout << "Exiting...\n";
            flag = 0;
            break;

        case 1:
            cout << endl;
            system("g++ TestClasses/Test_Aircraft.cpp -o TestClasses/Aircraft.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Aircraft.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;
        
        case 2:
            cout << endl;
            system("g++ TestClasses/Test_Combat.cpp -o TestClasses/Combat.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Combat.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 3:
            cout << endl;
            system("g++ TestClasses/Test_Stealth.cpp -o TestClasses/Stealth.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Stealth.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;
        
        case 4:
            cout << endl;
            system("g++ TestClasses/Test_Abductor.cpp -o TestClasses/Abductor.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Abductor.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 5:
            cout << endl;
            system("g++ TestClasses/Test_Guardian.cpp -o TestClasses/Guardian.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Guardian.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 6:
            cout << endl;
            system("g++ TestOperators/Test_AircraftStatusOperator.cpp -o TestOperators/AircraftStatusOperator.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AircraftStatusOperator.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;
        
        case 7:
            cout << endl;
            system("g++ TestOperators/Test_AircraftOperators.cpp -o TestOperators/AircraftOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AircraftOperators.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;
        
        case 8:
            cout << endl;
            system("g++ TestOperators/Test_CombatOperators.cpp -o TestOperators/CombatOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/CombatOperators.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 9:
            cout << endl;
            system("g++ TestOperators/Test_StealthOperators.cpp -o TestOperators/StealthOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/StealthOperators.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 10:
            cout << endl;
            system("g++ TestOperators/Test_AbductorOperators.cpp -o TestOperators/AbductorOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AbductorOperators.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 11:
            cout << endl;
            system("g++ TestOperators/Test_GuardianOperators.cpp -o TestOperators/GuardianOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/GuardianOperators.out");
            this_thread::sleep_for(chrono::seconds(1));
            break;

        case 12:
            cout << endl;
            system("g++ TestClasses/Test_Aircraft.cpp -o TestClasses/Aircraft.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Aircraft.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestClasses/Test_Combat.cpp -o TestClasses/Combat.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Combat.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestClasses/Test_Stealth.cpp -o TestClasses/Stealth.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Stealth.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestClasses/Test_Abductor.cpp -o TestClasses/Abductor.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Abductor.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestClasses/Test_Guardian.cpp -o TestClasses/Guardian.out -std=c++11 -Wno-div-by-zero && ./TestClasses/Guardian.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_AircraftStatusOperator.cpp -o TestOperators/AircraftStatusOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AircraftStatusOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_AircraftOperators.cpp -o TestOperators/AircraftOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AircraftOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_CombatOperators.cpp -o TestOperators/CombatOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/CombatOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_StealthOperators.cpp -o TestOperators/StealthOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/StealthOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_AbductorOperators.cpp -o TestOperators/AbductorOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/AbductorOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            system("g++ TestOperators/Test_GuardianOperators.cpp -o TestOperators/GuardianOperators.out -std=c++11 -Wno-div-by-zero && ./TestOperators/GuardianOperators.out");
            this_thread::sleep_for(chrono::milliseconds(250));
            break;

        default:
            cout << "No such test exists\n";
            break;
        }
    }
}

int main() {
    start();
    return 0;
}