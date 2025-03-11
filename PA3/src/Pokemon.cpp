//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Pokemon.cpp
#include "../include/Pokemon.hpp"
#include <algorithm> // For std::max

#include <iostream>

// Private expand function
void Pokemon::expandMoves(){

}

// Constructors
Pokemon::Pokemon()
{
    // Set defaults
    name = "Pikachu";
    type = "Electric";
    currentHP = 100;
    maxHP = 100;
    moveCount = 0;
    fainted = false;

    moveCapacity = 0;
    moves = NULL;
    equippedArmor = NULL;
}

Pokemon::Pokemon(const string& name, const string& type, int hp)
{
    // Initialize values

    this->name = name;
    this->type = type;
    this->currentHP = hp;
    this->maxHP = hp;
    this->moveCount = 0;
    fainted = false;

    moveCapacity = 1;
    moves = new Move[1];
    equippedArmor = NULL;

}

// Copy constructor
Pokemon::Pokemon(const Pokemon& other)
{
    // Copy basic data

    this->name = other.name;
    this->type = other.type;
    this->currentHP = other.currentHP;
    this->maxHP = other.maxHP;
    this->moveCount = other.moveCount;
    fainted = other.fainted;

    this->moveCapacity = other.moveCapacity;
    this->moves = new Move[other.moveCapacity];

    for (int i = 0; i < other.moveCount; i++)
    {
        this->moves[i] = other.moves[i];
    }

    
    if (other.equippedArmor != NULL)
    {
        this->equippedArmor = new Armor;
        this->equippedArmor[0] = other.equippedArmor[0];
    }
    else
    {
        this->equippedArmor = NULL;
    }
    
}

// Assignment operator
void Pokemon::copyFrom(const Pokemon &other)
{
    this->name = other.name;
    this->type = other.type;
    this->currentHP = other.currentHP;
    this->maxHP = other.maxHP;
    this->moveCount = other.moveCount;
    fainted = other.fainted;

    if (this->moves != NULL)
    {
        delete[] moves;
        moves = NULL;
    }
    
    if (this->equippedArmor != NULL)
    {
        delete equippedArmor;
        equippedArmor = NULL;
    }

    this->moveCapacity = other.moveCapacity;
    this->moves = new Move[other.moveCapacity];

    for (int i = 0; i < other.moveCount; i++)
    {
        this->moves[i] = other.moves[i];
    }

    
    if (other.equippedArmor != NULL)
    {
        this->equippedArmor = new Armor;
        this->equippedArmor[0] = other.equippedArmor[0];
    }

    // std::cout << "Here";

}

// Destructor
Pokemon::~Pokemon()
{
    if (moves != NULL)
    {
        delete[] moves;
    }

    if (equippedArmor != NULL)
    {
        delete equippedArmor;
    }

}

// Getters
string Pokemon::getName() const 
{ 
    return name;
}
string Pokemon::getType() const 
{ 
    return type;
}
int Pokemon::getMaxHP() const 
{ 
    return maxHP;
}
int Pokemon::getCurrentHP() const 
{ 
    return currentHP;
}
int Pokemon::getMoveCount() const
{ 
    return moveCount;
}
bool Pokemon::isFainted() const 
{ 
    return fainted;
}

Armor* Pokemon::getEquippedArmor() const 
{ 
    if (equippedArmor != NULL)
    {
        return equippedArmor;
    }

    return NULL;
    
}

Move* Pokemon::getMoveAtIndex(int index)
{
    return &moves[index];
}

// Move management
bool Pokemon::addMove(const Move& m)
{
    std::cout << "Here: " << m.getName();

    // Resizing Array
    if (++moveCount > moveCapacity)
    {
        Move *temp = new Move[moveCapacity * 2];

        for (int i = 0; i < moveCapacity; i++)
        {
            temp[i] = moves[i];
        }

        delete[] moves;
        
        moveCapacity *= 2;
        moves = temp;
        
    }


    moves[moveCount - 1] = m;
    
    return true;
}

bool Pokemon::removeMove(int index)
{
    return false;
}

bool Pokemon::hasMove(const string& moveName) const 
{
    return false;
}

// Battle functionality
void Pokemon::takeDamage(int amount)
{
    return;
}

void Pokemon::heal(int amount)
{
    return;
}

void Pokemon::equipArmor(const Armor& a)
{
    return;
}

void Pokemon::removeArmor(){
    return;
}

bool Pokemon::useMove(int moveIndex)
{
    return false;
}

bool Pokemon::usePotion(const Potion& p)
{
    return false;
}

void Pokemon::resetHP(){
    return;
}