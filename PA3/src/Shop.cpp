//// filepath: /F:/CS 200 TAship/CS_200_PA3s/NEWPA3/src/Shop.cpp
#include "../include/Shop.hpp"
#include <iostream>

// Private expansions
void Shop::expandPotions()
{
    // Resize Array
    Potion* temp = potions;

    potions = new Potion[potionCapacity * 2];

    // Copying data from Old Array into New

    for (int i = 0; i < potionCount - 1; i++)
    {
        potions[i] = temp[i];
    }

    // Deleting Old Array
    delete[] temp;

    potionCapacity *= 2;

    return;
}

void Shop::expandArmors()
{
    // Resize Array
    Armor* temp = armors;

    armors = new Armor[armorCapacity * 2];

    // Copying data from Old Array into New

    for (int i = 0; i < armorCount - 1; i++)
    {
        armors[i] = temp[i];
    }

    // Deleting Old Array
    delete[] temp;

    armorCapacity *= 2;
    return;
}

// Constructor
Shop::Shop()
{
    potionCount = 0;
    potionCapacity = 1;

    potions = new Potion[1];

    armorCount = 0;
    armorCapacity = 1;

    armors = new Armor[1];
}

// Destructor
Shop::~Shop()
{
    delete[] potions;
    delete[] armors;
}

// Inventory management
void Shop::addPotion(const Potion &p)
{
    if (++potionCount > potionCapacity)
    {
        expandPotions();
    }

    potions[potionCount - 1] = p;
    
    return;
}

void Shop::addArmor(const Armor &a)
{
    if (++armorCount > armorCapacity)
    {
        expandArmors();
    }

    armors[armorCount - 1] = a;

    return;
}

bool Shop::removePotion(int index)
{
    if (index < 0 || index > potionCount - 1)
    {
        return false;
    }

    for (int i = index; i < potionCount - 1; i++)
    {
        potions[i] = potions[i + 1];
    }

    potionCount--;
    
    return true;
}

bool Shop::removeArmor(int index)
{
    if (index < 0 || index > armorCount - 1)
    {
        return false;
    }

    for (int i = index; i < armorCount - 1; i++)
    {
        armors[i] = armors[i + 1];
    }

    armorCount--;
    
    return true;
}

// Getters
int Shop::getPotionCount() const 
{ 
    return potionCount;
}
int Shop::getArmorCount() const 
{ 
    return armorCount;
}

Potion *Shop::getPotionAtIndex(int index) const
{
    if (index < 0 || index >= potionCapacity)
    {
        return nullptr;
    }
    
    return (potions + index);
}

Armor *Shop::getArmorAtIndex(int index) const
{
    if (index < 0 || index >= armorCapacity)
    {
        return nullptr;
    }
    
    return (armors + index);
}

// Shopping functionality
bool Shop::sellPotionTo(int potionIndex, Trainer &buyer)
{
    if (potionIndex >= potionCount)
    {
        return false;
    }

    if (potions[potionIndex].getCost() > buyer.getMoney())
    {
        return false;
    }

    buyer.addPotion(potions[potionIndex]);
    buyer.spendMoney(potions[potionIndex].getCost());

    removePotion(potionIndex);

    return true;
}

bool Shop::sellArmorTo(int armorIndex, Trainer &buyer, int pokemonIndex)
{
    if (armorIndex >= armorCount)
    {
        return false;
    }

    if (armors[armorIndex].getDefenseBonus() * 10 > buyer.getMoney())
    {
        return false;
    }

    if (!buyer.getPokemonAtIndex(pokemonIndex))
    {
        return false;
    }
    

    buyer.spendMoney(armors[armorIndex].getDefenseBonus() * 10);
    buyer.getPokemonAtIndex(pokemonIndex)->equipArmor(armors[armorIndex]);

    removeArmor(armorIndex);

    return true;
}

void Shop::displayInventory() const
{
    cout << "----- Potions -----" << endl;
    cout << endl;

    for (int i = 0; i < potionCount; i++)
    {
        cout << "Potion: " << potions[i].getName() << endl;
        cout << "Heal Amount: " <<  potions[i].getHealAmount() << endl;
        cout << "Cost: " << potions[i].getCost() << endl;
        cout << endl;
    }

    cout << "----- Armors -----" << endl;
    cout << endl;
    
    for (int i = 0; i < armorCount; i++)
    {
        cout << "Potion: " << armors[i].getName() << endl;
        cout << "Defence Bonus: " <<  armors[i].getDefenseBonus() << endl;
        cout << "Weight: " << armors[i].getWeight() << endl;
        cout << "Cost: " << armors[i].getDefenseBonus() * 10 << endl;
        cout << endl;
    }
    
    return;
}