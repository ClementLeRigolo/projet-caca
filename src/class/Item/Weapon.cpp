#include "class/Item.hpp"

Weapon::Weapon() : Item() {}

Weapon::Weapon(int id, string name, string description, Texture texture, float damage, float attackSpeed)
    : Item(id, name, description, texture, true), m_damage(damage), m_attackSpeed(attackSpeed) {}

float Weapon::getDamage() const { return m_damage; }

void Weapon::setDamage(float damage) { m_damage = damage; }

float Weapon::getAttackSpeed() const { return m_attackSpeed; }

void Weapon::setAttackSpeed(float attackSpeed) { m_attackSpeed = attackSpeed; }