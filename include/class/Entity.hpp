#pragma once

#include "libs.hpp"

class Entity {
    private:
        Sprite m_sprite;
        RectangleShape m_box;
        float m_speed;
        float m_health;
        Vector2f m_velocity;
    
    public:
        Entity();
};
