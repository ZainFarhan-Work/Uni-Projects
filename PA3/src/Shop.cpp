//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Shop.cpp
#include "../include/Shop.hpp"
#include <iostream>

// Private expansions
void Shop::expandPotions()
{
    return;
}

void Shop::expandArmors()
{
    return;
}

// Constructor
Shop::Shop()
{

}

// Destructor
Shop::~Shop()
{

}

// Inventory management
void Shop::addPotion(const Potion &p)
{
    return;
}

void Shop::addArmor(const Armor &a)
{
    return;
}

bool Shop::removePotion(int index)
{
    return false;
}

bool Shop::removeArmor(int index)
{
    return false;
}

// Getters
int Shop::getPotionCount() const 
{ 
    return -1;
}
int Shop::getArmorCount() const 
{ 
    return -1;
}

Potion *Shop::getPotionAtIndex(int index) const
{
    return nullptr;
}

Armor *Shop::getArmorAtIndex(int index) const
{
    return nullptr;
}

// Shopping functionality
bool Shop::sellPotionTo(int potionIndex, Trainer &buyer)
{
    return true;
}

bool Shop::sellArmorTo(int armorIndex, Trainer &buyer, int pokemonIndex)
{
    return false;
}

void Shop::displayInventory() const
{
    return;
}