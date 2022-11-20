#pragma once

#include "libs.hpp"

class Collider : public RectangleShape
{
    public:
        Collider();

        Vector2f m_vel;
        Vector2f m_acc;

        bool checkCollision(Collider& other, float push);
    
        Vector2f getHalfSize();
};