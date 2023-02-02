#pragma once

#include "libs.hpp"

namespace Collision {
    enum Side {
        NONE,
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
    };
}

class CollisionInfo
{
    private:
        const RectangleShape* m_shape;
        Collision::Side m_side;

    public:
        CollisionInfo();
        CollisionInfo(const RectangleShape* shape, Collision::Side side);
        const RectangleShape* getShape();
        Collision::Side getSide();
};

class Collider : public RectangleShape
{
    private:
        bool m_gravityEnabled;
        float m_gravityMultiplier;

    public:
        Collider();
        Collider(const sf::Texture*, sf::Vector2f size, sf::Vector2f pos);
        Collider(const RectangleShape& shape);

        Vector2f m_vel;
        Vector2f m_acc;
        float m_friction;

        CollisionInfo checkCollision(Collider& other, float push);
        bool isGravityEnabled();
        void setGravityEnabled(bool toggle);
        float getGravityMultiplier();
        void setGravityMultiplier(float multiplier);

        Vector2f getHalfSize();
};
