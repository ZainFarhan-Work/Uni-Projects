#ifndef ACS_61_H
#define ACS_61_H

#include <iostream>
#include <string>
using namespace std;
/* 
Include only ATTRIBUTES and FUNCTION SIGNATURES for each class in this file. 
Code for each method must be in ACS_61.cpp 
i.e.
class Aeroplane {
    private:
        string name;
    public:
        string get_name();
};
*/

enum class AircraftStatus {
    OnGround,
    Airborne,
    Crashed
};

// BASE CLASS
class Aircraft {
    private:
        string identifier;
        int fuel_level;
        int health;
        AircraftStatus current_status;
    //
};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft {
    private:
        string weapon_type;
        int weapon_count;
        int weapon_strength;
    //
};

class StealthAircraft {
    private:
        bool cloak_status;
    //
};

class AbductorCraft {
    private:
        int abductee_count;
        int abductee_capacity;    
    //
};

class GuardianCraft {
    private:
        int kill_count;
    //
};

#endif