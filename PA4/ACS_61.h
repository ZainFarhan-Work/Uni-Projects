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

ostream& operator<<(ostream& out, const AircraftStatus status);

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
        Aircraft(const Aircraft& copy);

        // Essential Functions

        void takeOff();
        void land();

        // Operator

        virtual Aircraft& operator+=(const int fuel);
        virtual Aircraft& operator-=(const int fuel);
        bool operator==(const Aircraft& other);

        friend ostream& operator<<(ostream& out, const Aircraft& craft);
        friend istream& operator>>(istream& in, Aircraft& craft);

        // Getters
        virtual string getIdentifier();
        virtual int getFuelLevel();
        virtual int getHealth();
        virtual AircraftStatus getCurrentStatus();
};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft : public virtual Aircraft
{
    protected:
        string weapon_type;
        int weapon_count;
        int weapon_strength;
    //
    public:

        // Constructors
        CombatAircraft();
        CombatAircraft(string identifier, int fuel, int health, AircraftStatus status,
        string weapon, int weapon_count, int weapon_strength); 
        CombatAircraft(const CombatAircraft& copy);

        // Operators

        CombatAircraft operator++(int);
        CombatAircraft& operator--();

        friend ostream& operator<<(ostream& out, const CombatAircraft& craft);

        // Getters
        string getWeaponType();
        int getWeaponCount();
        int getWeaponStrength();

};

class StealthAircraft : public virtual Aircraft
{
    protected:
        bool cloak_status;
    //
    public:

        // Constructors

        StealthAircraft();
        StealthAircraft(string identifier, int fuel, int health, AircraftStatus status, bool cloak);
        StealthAircraft(const StealthAircraft& copy);

        // Essential Functions

        void takeOff();
        void land();

        void activateCloak();
        void deactivateCloak();

        // Operators

        bool operator!();

        friend ostream& operator<<(ostream& out, const StealthAircraft& craft);

        // Getters

        bool getCloakStatus();

};

class AbductorCraft : public virtual StealthAircraft
{
    private:
        int abductee_count;
        int abductee_capacity;    
    //

    public:

        // Constructors

        AbductorCraft();
        AbductorCraft(string identifier, int fuel, int health, AircraftStatus status, bool cloak, int abductee_count, int capacity);
        AbductorCraft(const AbductorCraft& copy);

        // Operators
        bool operator>(const AbductorCraft& other);
        
        AbductorCraft& operator+=(const int fuel);
        AbductorCraft& operator-=(const int fuel);
        
        AbductorCraft& operator&(AbductorCraft& other);
        
        friend ostream& operator<<(ostream& out, const AbductorCraft& craft);

        // Helper Functions

        void setHealth(int num);
        void decreaseHealth(int num);

        void setStatus(AircraftStatus status);

        // Getters

        int getAbducteeCount();
        int getAbducteeCapacity();
};

class GuardianCraft : public virtual CombatAircraft, public virtual StealthAircraft
{
    private:
        int kill_count;
    //
    public:

        // Constructors

        GuardianCraft();
        GuardianCraft(string identifier, int fuel, int health, AircraftStatus status,
            string weapon, int weapon_count, int weapon_strength, bool cloak, int kill_count);
        GuardianCraft(const GuardianCraft& copy);

        // Operators

        bool operator*=(AbductorCraft& abductor);
        bool operator*(AbductorCraft& abductor);

        GuardianCraft operator++(int);
        GuardianCraft& operator--();

        friend ostream& operator<<(ostream& out, const GuardianCraft& craft);

        // Getters

        int getKillCount();
};

#endif