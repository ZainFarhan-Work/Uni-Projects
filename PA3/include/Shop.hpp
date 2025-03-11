#ifndef SHOP_HPP
#define SHOP_HPP

#include "Potion.hpp"
#include "Armor.hpp"
#include "Trainer.hpp"
using namespace std;

class Shop
{
private:
    Potion *potions; // Dynamic array of potions
    int potionCount;
    int potionCapacity;
    Armor *armors; // Dynamic array of armors
    int armorCount;
    int armorCapacity;

    void expandPotions();
    void expandArmors();

public:
    // Constructors and destructor
    Shop();
    ~Shop();

    // No copy constructor or assignment - shop is unique

    // Inventory management
    void addPotion(const Potion &p);
    void addArmor(const Armor &a);
    bool removePotion(int index);
    bool removeArmor(int index);

    // Getters
    int getPotionCount() const;
    int getArmorCount() const;
    Potion *getPotionAtIndex(int index) const;
    Armor *getArmorAtIndex(int index) const;

    // Shopping functionality
    bool sellPotionTo(int potionIndex, Trainer &buyer);
    bool sellArmorTo(int armorIndex, Trainer &buyer, int pokemonIndex);
    void displayInventory() const;
};

#endif