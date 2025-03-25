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

enum class AircraftStatus
{
    OnGround,
    Airborne,
    Crashed
};

// BASE CLASS
class Aircraft
{
    protected:
        string identifier;
        int fuel_level;
        int health;
        AircraftStatus current_status;

        int const MAX_AMOUNT = 100;

    //
    public:

        // Construcrors
        Aircraft();
        Aircraft(string identifier, int fuel, int health, AircraftStatus status);
        Aircraft(Aircraft& copy);

        // Essential Functions
        string getIdentifier();
        int getFuelLevel();
        int getHealth();
        AircraftStatus getCurrentStatus();

        void takeOff();
        void land();

};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft : public Aircraft
{
    protected:
        string weapon_type;
        int weapon_count;
        int weapon_strength;
    //
    public:

        // Constructors
        CombatAircraft();
        CombatAircraft(string identifier, int fuel, int health, AircraftStatus status, string weapon, int weapon_count, int weapon_strength); 
        CombatAircraft(CombatAircraft& copy);

        // Essential Functions
        string getWeaponType();
        int getWeaponCount();
        int getWeaponStrength();

};

class StealthAircraft : public Aircraft
{
    private:
        bool cloak_status;
    //
    public:

        // Constructors

        StealthAircraft();
        StealthAircraft(string identifier, int fuel, int health, AircraftStatus status, bool cloak);
        StealthAircraft(StealthAircraft& copy);

        // Essential Functions

        void takeOff();
        void land();

        void activateCloak();
        void deactivateCloak();

        // Getters

        bool getCloakStatus();

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