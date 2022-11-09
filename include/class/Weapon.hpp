#pragma once

#include "class/Item.hpp"

class Weapon : public Item
{
    private:
        float m_damage;
        float m_attackSpeed;
    
    public:
        Weapon();
        Weapon(int id, string name, string description, Texture texture, float damage, float attackSpeed);
        float getDamage() const;
        void setDamage(float damage);
        float getAttackSpeed() const;
        void setAttackSpeed(float attackSpeed);
};