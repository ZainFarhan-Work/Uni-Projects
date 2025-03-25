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
    GuardianCraft gc2("GRD1", 25, 69, AircraftStatus::Airborne, "Llamas", 10, 25, true, 2);

    cout << gc2.getIdentifier() << endl;
    cout << gc2.getHealth() << endl;

}