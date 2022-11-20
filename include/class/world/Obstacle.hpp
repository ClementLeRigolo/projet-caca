#pragma once

#include "libs.hpp"
#include "class/Collider.hpp"

class Obstacle
{
    private:
        Collider m_shape;
    public:
        Obstacle(Vector2f pos, Vector2f size);
        RectangleShape& getShape();
        Collider& getCollider();
};