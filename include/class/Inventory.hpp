#pragma once

#include "class/Item.hpp"

class Inventory
{
    private:
        Item m_items[16];
        Weapon m_mainSlot;

    public:
        Inventory();
        Item& getItem(int slot);
        void setItem(int slot, Item item);
        Item* getItems();
        Weapon& getWeapon();
        void setWeapon(Weapon weapon);
        void clear();
};