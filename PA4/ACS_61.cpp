#include "ACS_61.h"

/* 
Implement all class methods here.
i.e.
string Aeroplane::get_name() {
    return this->name;
}
*/

// Aircraft Status

ostream& operator<<(ostream& out, const AircraftStatus status)
{
    switch (status)
    {
    case AircraftStatus::OnGround:
        out << "On Ground";
        break;

    case AircraftStatus::Airborne:
        out << "Airborne";
        break;

    case AircraftStatus::Crashed:
        out << "Crashed";
        break;
    
    default:
        out << "Unknown";
        break;
    }

    return out;
}


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

Aircraft::Aircraft(const Aircraft& copy)
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

Aircraft& Aircraft::operator+=(const int fuel)
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    fuel_level += fuel;

    if (fuel_level > 100)
    {
        fuel_level = 100;
    }

    if (fuel_level < 0)
    {
        fuel_level = 0;
    }
    
    return *this;
    
}

Aircraft& Aircraft::operator-=(const int fuel)
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    fuel_level -= fuel;

    if (fuel_level > 100)
    {
        fuel_level = 100;
    }

    if (fuel_level < 0)
    {
        fuel_level = 0;
    }

    return *this;
}

bool Aircraft::operator==(const Aircraft& other)
{
    if (identifier == other.identifier && fuel_level == other.fuel_level && health == other.health && current_status == other.current_status)
    {
        return true;
    }
    
    return false;

}

ostream& operator<<(ostream& out, const Aircraft& craft)
{
    out << "Identifier: " << craft.identifier << endl;
    out << "Fuel Level: " << craft.fuel_level << "%"  << endl;
    out << "Health: " << craft.health << "%" << endl;
    out << "Current Status: " << craft.current_status << endl;
    return out;
}

istream& operator>>(istream& in, Aircraft& craft)
{
    int status = 0;

    cout << "Identifier: ";
    in >> craft.identifier;
    cout << "Fuel Level: ";
    in >> craft.fuel_level;
    cout << "Health: ";
    in >> craft.health;
    cout << "Status [0-2]: ";
    in >> status;

    if (craft.fuel_level > 100)
    {
        craft.fuel_level = 100;
    }
    else if (craft.fuel_level < 0)
    {
        craft.fuel_level = 0;
    }
    
    if (craft.health > 100)
    {
        craft.health = 100;
    }
    else if (craft.health < 0)
    {
        craft.health = 0;
    }

    switch (status)
    {
    default:
    case 0:
        craft.current_status = AircraftStatus::OnGround;
        break;
    case 1:
        craft.current_status = AircraftStatus::Airborne;
        break;
    case 2:
        craft.current_status = AircraftStatus::Crashed;
        break;
    }

    return in;
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

CombatAircraft::CombatAircraft(const CombatAircraft& copy) : Aircraft(copy)
{
    weapon_type = copy.weapon_type;
    weapon_count = copy.weapon_count;
    weapon_strength = copy.weapon_strength;
}


// Operators

CombatAircraft CombatAircraft::operator++(int)
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    CombatAircraft temp = *this;

    weapon_count++;

    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    
    return temp;
}

CombatAircraft& CombatAircraft::operator--()
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    weapon_count--;

    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    
    return *this;
}

ostream& operator<<(ostream& out, const CombatAircraft& craft)
{
    out << "Identifier: " << craft.identifier << endl;
    out << "Fuel Level: " << craft.fuel_level << "%"  << endl;
    out << "Health: " << craft.health << "%" << endl;
    out << "Current Status: " << craft.current_status << endl;
    out << "Weapon Type: " << craft.weapon_type << endl;
    out << "Weapon Count: " << craft.weapon_count << endl;
    out << "Weapon Strength: " << craft.weapon_strength << endl;
    
    return out;
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

StealthAircraft::StealthAircraft(const StealthAircraft& copy) : Aircraft(copy)
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
    if (current_status == AircraftStatus::Crashed  || cloak_status == true || current_status == AircraftStatus::OnGround)
    {
        return;
    }

    health -= 10;

    if (health <= 0)
    {
        current_status = AircraftStatus::Crashed;
        health = 0;

        return;
    }
    
    fuel_level -= 15;

    if (fuel_level <= 0 && current_status == AircraftStatus::Airborne)
    {
        current_status = AircraftStatus::Crashed;
        health = 0;
        fuel_level = 0;
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


// Operators

bool StealthAircraft::operator!()
{
    if (getCloakStatus())
    {
        deactivateCloak();
        return false;
    }
    else if (!getCloakStatus())
    {
        activateCloak();
        return true;
    }

    return false;
    
}

ostream& operator<<(ostream& out, const StealthAircraft& craft)
{
    out << "Identifier: " << craft.identifier << endl;
    out << "Fuel Level: " << craft.fuel_level << "%"  << endl;
    out << "Health: " << craft.health << "%" << endl;
    out << "Current Status: " << craft.current_status << endl;

    if (craft.cloak_status)
    {
        out << "Cloak Status: On" << endl;
    }
    else out << "Cloak Status: Off" << endl;

    return out;
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
    if (capacity < 0)
    {
        capacity = abductee_count;
    }
    
    if (abductee_count > capacity)
    {
        abductee_count = capacity;
    }
    else if (abductee_count < 0)
    {
        abductee_count = 0;
    }

    // if (capacity > MAX_AMOUNT)
    // {
    //     capacity = MAX_AMOUNT;
    // }

    this->abductee_count = abductee_count;
    this->abductee_capacity = capacity;
}

AbductorCraft::AbductorCraft(const AbductorCraft& copy) :
Aircraft(copy),
StealthAircraft(copy)
{
    this->abductee_count = copy.abductee_count;
    this->abductee_capacity = copy.abductee_capacity;
}


// Operators

bool AbductorCraft::operator>(const AbductorCraft& other)
{
    double this_ratio = (double) abductee_count / abductee_capacity;
    double other_ratio = (double) other.abductee_count / other.abductee_capacity;

    // cout << "This Values: " << abductee_count << " / " << abductee_capacity << endl;
    // cout << "This: " << this_ratio << endl;
    // cout << "Other: " << other_ratio << endl;
    // cout << endl;

    if (this_ratio > other_ratio)
    {
        return true;
    }
    
    return false;

}

AbductorCraft& AbductorCraft::operator+=(const int fuel)
{
    if (current_status == AircraftStatus::Airborne)
    {
        abductee_count += fuel;

        if (abductee_count > abductee_capacity)
        {
            abductee_count = abductee_capacity;
        }

        if (abductee_count < 0)
        {
            abductee_count = 0;
        }
           
    }

    else Aircraft::operator+=(fuel);
    
    return *this;

}

AbductorCraft& AbductorCraft::operator-=(const int fuel)
{
    if (current_status == AircraftStatus::Airborne)
    {
        abductee_count -= fuel;

        if (abductee_count > abductee_capacity)
        {
            abductee_count = abductee_capacity;
        }

        if (abductee_count < 0)
        {
            abductee_count = 0;
        }
           
    }

    else Aircraft::operator-=(fuel);

    return *this;
}

AbductorCraft& AbductorCraft::operator&(AbductorCraft& other)
{
    if (current_status != AircraftStatus::Airborne || other.current_status != AircraftStatus::Airborne)
    {
        return *this;
    }
    
    if (other.abductee_capacity > abductee_capacity)
    {
        other.health += health;

        if (other.health > MAX_AMOUNT)
        {
            other.health = MAX_AMOUNT;
        }

        other.fuel_level += fuel_level;

        if (other.fuel_level > MAX_AMOUNT)
        {
            other.fuel_level = MAX_AMOUNT;
        }

        other.abductee_count += abductee_count;
        other.abductee_capacity += abductee_capacity;

        // Resetting the Non-Merged Plane
        health = 0;
        fuel_level = 0;
        abductee_count = 0;
        abductee_capacity = 0;

        current_status = AircraftStatus::Crashed;

        cloak_status = false;
        
        return other;
        
    }

    else
    {
        health +=  other.health;

        if (health > MAX_AMOUNT)
        {
            health = MAX_AMOUNT;
        }

        fuel_level +=  other.fuel_level;

        if (fuel_level > MAX_AMOUNT)
        {
            fuel_level = MAX_AMOUNT;
        }

        abductee_count +=  other.abductee_count;
        abductee_capacity += other.abductee_capacity;

        // Resetting the Non-Merged Plane
        other.health = 0;
        other.fuel_level = 0;
        other.abductee_count = 0;
        other.abductee_capacity = 0;

        other.current_status = AircraftStatus::Crashed;

        other.cloak_status = false;
        
        return *this;
    }
    
}


ostream& operator<<(ostream& out, const AbductorCraft& craft)
{
    out << "Identifier: " << craft.identifier << endl;
    out << "Fuel Level: " << craft.fuel_level << "%"  << endl;
    out << "Health: " << craft.health << "%" << endl;
    out << "Current Status: " << craft.current_status << endl;

    if (craft.cloak_status)
    {
        out << "Cloak Status: On" << endl;
    }
    else out << "Cloak Status: Off" << endl;

    out << "Abductee Count: " << craft.abductee_count << endl;
    out << "Abductee Capacity: " << craft.abductee_capacity << endl;

    return out;
}

// Helper Functions

void AbductorCraft::setHealth(int num) { health = num; }
void AbductorCraft::decreaseHealth(int num) { health -= num; }
void AbductorCraft::setStatus(AircraftStatus status) { current_status = status; }

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

GuardianCraft::GuardianCraft(const GuardianCraft& copy) :
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

GuardianCraft GuardianCraft::operator++(int)
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    GuardianCraft temp = *this;

    weapon_count++;

    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    
    return temp;
}

GuardianCraft& GuardianCraft::operator--()
{
    if (current_status != AircraftStatus::OnGround)
    {
        return *this;
    }

    weapon_count--;

    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    
    return *this;
}

bool GuardianCraft::operator*=(AbductorCraft& abductor)
{
    if ((current_status == AircraftStatus::Airborne && abductor.getCurrentStatus() == AircraftStatus::Airborne) && (!abductor.getCloakStatus() && abductor.getAbducteeCount() == 0) && weapon_count > 0)
    {
        return true;
    }
    
    return false;
}

bool GuardianCraft::operator*(AbductorCraft& abductor)
{
    if (*this *= abductor)
    {
        weapon_count--;

        abductor.decreaseHealth(weapon_strength);

        if (abductor.getHealth() <= 0)
        {
            abductor.setHealth(0);
            abductor.setStatus(AircraftStatus::Crashed);
            kill_count++;
        }

        return true;
        
    }
    
    return false;
}

ostream& operator<<(ostream& out, const GuardianCraft& craft)
{
    out << "Identifier: " << craft.identifier << endl;
    out << "Fuel Level: " << craft.fuel_level << "%"  << endl;
    out << "Health: " << craft.health << "%" << endl;
    out << "Current Status: " << craft.current_status << endl;
    out << "Weapon Type: " << craft.weapon_type << endl;
    out << "Weapon Count: " << craft.weapon_count << endl;
    out << "Weapon Strength: " << craft.weapon_strength << endl;

    if (craft.cloak_status)
    {
        out << "Cloak Status: On" << endl;
    }
    else out << "Cloak Status: Off" << endl;

    out << "Kill Count: " << craft.kill_count << endl;

    return out;
}

// Getters

int GuardianCraft::getKillCount() { return kill_count; }

#pragma endregion


