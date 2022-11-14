#include "class/Inventory.hpp"

Inventory::Inventory() {}

Item& Inventory::getItem(int slot) { return m_items[slot]; }

void Inventory::setItem(int slot, Item item) { m_items[slot] = item; }

Item* Inventory::getItems() { return m_items; }

Weapon& Inventory::getWeapon() { return m_mainSlot; }

void Inventory::setWeapon(Weapon weapon) { m_mainSlot = weapon; }

void Inventory::clear()
{
    for (int i = 0; i != 15; i++)
        setItem(i, Item());
}