#pragma once

#include "libs.hpp"

enum CollisionSide {
    C_NONE,
    C_LEFT,
    C_RIGHT,
    C_TOP,
    C_BOTTOM,
};

class CollisionInfo
{
    private:
        const RectangleShape* m_shape;
        CollisionSide m_side;

    public:
        CollisionInfo(const RectangleShape* shape, CollisionSide side);
        const RectangleShape* getShape();
        CollisionSide getSide();
};

class Collider : public RectangleShape
{
    public:
        Collider();

        Vector2f m_vel;
        Vector2f m_acc;
        float m_friction;

        CollisionInfo checkCollision(Collider& other, float push);
    
        Vector2f getHalfSize();
};
