#include <iostream>
#include <sstream>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <iomanip> 
#include <cstdlib>

#include "ACS_61.h"
#include "ACS_61.cpp"

using namespace std;

int main()
{
    Aircraft a1("AIRCRFT1", 48, 93, AircraftStatus::OnGround);
    CombatAircraft ca1("", 100, 100, AircraftStatus::OnGround, "Missiles", 7, 25);
    AbductorCraft ac1("", 23, 100, AircraftStatus::OnGround, false, 0, 200);
    GuardianCraft gc2("GRD1", 25, 69, AircraftStatus::OnGround, "Llamas", 10, 25, true, 2);

    cout << ac1.getFuelLevel() << endl;
    cout << gc2.getFuelLevel() << endl;

    ac1 += 22;
    gc2 += 25;

    cin >> a1;

    cout << ca1.getWeaponCount();
    // cout << endl;
    // cout << ac1.getHealth() << endl;
    // cout << ac1.getCurrentStatus() << endl;
    // cout << ac1.getAbducteeCapacity() << endl;
    // cout << ac1.getFuelLevel() << endl;
    // cout << gc2.getFuelLevel() << endl;

}