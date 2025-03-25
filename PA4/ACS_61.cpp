#include "ACS_61.h"

/* 
Implement all class methods here.
i.e.
string Aeroplane::get_name() {
    return this->name;
}
*/


// Aircraft methods

#pragma region Aircraft

// Constructors

Aircraft::Aircraft()
{
    identifier = "";
    fuel_level = 100;
    health = 100;
    current_status = AircraftStatus::OnGround;
}

Aircraft::Aircraft(string identifier, int fuel, int health, AircraftStatus status)
{
    if (fuel > MAX_AMOUNT)
    {
        fuel = MAX_AMOUNT;
    }
    else if (fuel < 0)
    {
        fuel = 0;
    }

    if (health > MAX_AMOUNT)
    {
        health = MAX_AMOUNT;
    }
    else if (health <= 0 || (status == AircraftStatus::Airborne && fuel == 0))
    {
        health = 0;
        status = AircraftStatus::Crashed;
    }
    
    this->identifier = identifier;
    this->fuel_level = fuel;
    this->health = health;
    this->current_status = status;
}

Aircraft::Aircraft(Aircraft& copy)
{
    identifier = copy.identifier;
    fuel_level = copy.fuel_level;
    health = copy.health;
    current_status = copy.current_status;
}


// Essential Functions

void Aircraft::takeOff()
{
    if (current_status == AircraftStatus::Crashed || fuel_level < 30)
    {
        return;
    }

    current_status = AircraftStatus::Airborne;
    
    return;
}

void Aircraft::land()
{
    if (current_status == AircraftStatus::Crashed)
    {
        return;
    }

    current_status = AircraftStatus::OnGround;
    
    return;

}


// Operators

ostream& operator<<(ostream& out, const Aircraft& craft)
{
    return out;
}


// Getters

string Aircraft::getIdentifier() { return identifier; }
int Aircraft::getFuelLevel() { return fuel_level; }
int Aircraft::getHealth() { return health; }
AircraftStatus Aircraft::getCurrentStatus() { return current_status; }

#pragma endregion


// CombatAircraft methods

#pragma region Combat Aircraft

// Constructors

CombatAircraft::CombatAircraft() : Aircraft()
{
    weapon_type = "";
    weapon_count = 0;
    weapon_strength = 0;
}

CombatAircraft::CombatAircraft(string identifier, int fuel, int health, AircraftStatus status, string weapon, int weapon_count, int weapon_strength)
: Aircraft(identifier, fuel, health, status)
{
    // if (weapon_count > MAX_AMOUNT)
    // {
    //     weapon_count = MAX_AMOUNT;
    // }
    if (weapon_count < 0)
    {
        weapon_count = 0;
    }

    if (weapon_strength > MAX_AMOUNT)
    {
        weapon_strength = MAX_AMOUNT;
    }
    else if (weapon_strength < 0)
    {
        weapon_strength = 0;
    }

    this->weapon_type = weapon;
    this->weapon_count = weapon_count;
    this->weapon_strength = weapon_strength;
}

CombatAircraft::CombatAircraft(CombatAircraft& copy) : Aircraft(copy)
{
    weapon_type = copy.weapon_type;
    weapon_count = copy.weapon_count;
    weapon_strength = copy.weapon_strength;
}




// Getters

string CombatAircraft::getWeaponType() { return weapon_type; }
int CombatAircraft::getWeaponCount() { return weapon_count; }
int CombatAircraft::getWeaponStrength() { return weapon_strength; }

#pragma endregion


// StealthAircraft methods

#pragma region Stealth Aircraft


// Constructors

StealthAircraft::StealthAircraft() : Aircraft()
{
    cloak_status = false;
}

StealthAircraft::StealthAircraft(string identifier, int fuel, int health, AircraftStatus status, bool cloak)
: Aircraft(identifier, fuel, health, status)
{
    if (current_status != AircraftStatus::Airborne)
    {
        cloak = false;
    }
    
    cloak_status = cloak;
}

StealthAircraft::StealthAircraft(StealthAircraft& copy) : Aircraft(copy)
{
    cloak_status = copy.cloak_status;
}


// Essential Functions

void StealthAircraft::takeOff()
{
    if (cloak_status)
    {
        cloak_status = false;
    }
    
    Aircraft::takeOff();

}

void StealthAircraft::land()
{
    if (cloak_status)
    {
        cloak_status = false;
    }
    
    Aircraft::land();
}

void StealthAircraft::activateCloak()
{
    if (current_status == AircraftStatus::Crashed || (fuel_level - 15 < 0 || health - 10 < 0) || cloak_status == true)
    {
        return;
    }

    health -= 10;

    if (health <= 0)
    {
        current_status = AircraftStatus::Crashed;

        return;
    }
    
    fuel_level -= 15;

    if (fuel_level <= 0 && current_status == AircraftStatus::Airborne)
    {
        current_status = AircraftStatus::Crashed;
        health = 0;
        return;
    }
    
    cloak_status = true;
}

void StealthAircraft::deactivateCloak()
{
    if (current_status == AircraftStatus::Crashed)
    {
        return;
    }

    cloak_status = false;
    
}


// Getters

bool StealthAircraft::getCloakStatus() { return cloak_status; }

#pragma endregion


// AbductorCraft methods

#pragma region Abductor Aircraft

// Constructors

AbductorCraft::AbductorCraft() : Aircraft(),  StealthAircraft()
{
    abductee_count = 0;
    abductee_capacity = 0;
}

AbductorCraft::AbductorCraft(string identifier, int fuel, int health, AircraftStatus status, bool cloak, int abductee_count, int capacity) :
Aircraft(identifier, fuel, health, status),
StealthAircraft(identifier, fuel, health, status, cloak)
{
    if (abductee_count > MAX_AMOUNT)
    {
        abductee_count = MAX_AMOUNT;
    }
    else if (abductee_count < 0)
    {
        abductee_count = 0;
    }

    if (capacity > MAX_AMOUNT)
    {
        capacity = MAX_AMOUNT;
    }
    else if (capacity < 0)
    {
        capacity = abductee_count;
    }

    this->abductee_count = abductee_count;
    this->abductee_capacity = capacity;
}

AbductorCraft::AbductorCraft(AbductorCraft& copy) :
Aircraft(copy),
StealthAircraft(copy)
{
    this->abductee_count = copy.abductee_count;
    this->abductee_capacity = copy.abductee_capacity;
}

// Getters

int AbductorCraft::getAbducteeCount() { return abductee_count; }
int AbductorCraft::getAbducteeCapacity() { return abductee_capacity; }

#pragma endregion


// GuardianCraft methods


#pragma region Guardian Aircraft

// Constructors

GuardianCraft::GuardianCraft() : Aircraft(), CombatAircraft(), StealthAircraft()
{
    kill_count = 0;
}

GuardianCraft::GuardianCraft(string identifier, int fuel, int health, AircraftStatus status,
    string weapon, int weapon_count, int weapon_strength, bool cloak, int kill_count) :
    Aircraft(identifier, fuel, health, status),
    CombatAircraft(identifier, fuel, health, status, weapon, weapon_count, weapon_strength),
    StealthAircraft(identifier, fuel, health, status, cloak)
    {
        if (kill_count > MAX_AMOUNT)
        {
            kill_count = MAX_AMOUNT;
        }
        else if (kill_count < 0)
        {
            kill_count = 0;
        }
        
        
        this->kill_count = kill_count;
    }

GuardianCraft::GuardianCraft(GuardianCraft& copy) :
Aircraft(copy),
CombatAircraft(copy),
StealthAircraft(copy)
{
    if (kill_count > MAX_AMOUNT)
    {
        kill_count = MAX_AMOUNT;
    }
    else if (kill_count < 0)
    {
        kill_count = 0;
    }
    kill_count = copy.kill_count;
}


// Operators

// Getters

int GuardianCraft::getKillCount() { return kill_count; }

#pragma endregion


