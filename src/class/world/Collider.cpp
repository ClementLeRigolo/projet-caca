#include "class/Collider.hpp"

CollisionInfo::CollisionInfo(const RectangleShape* shape, CollisionSide side)
{
    m_shape = shape;
    m_side = side;
}

const RectangleShape* CollisionInfo::getShape()
{
    return m_shape;
}

CollisionSide CollisionInfo::getSide()
{
    return m_side;
}

Collider::Collider()
{
    m_acc = Vector2f(0.0f, 0.0f);
    m_vel = Vector2f(0.0f, 0.0f);
    m_friction = 0.5;
}

Vector2f Collider::getHalfSize()
{
    return Vector2f(getGlobalBounds().width / 2.0, getGlobalBounds().height / 2.0);
}

CollisionInfo Collider::checkCollision(Collider& other, float push)
{
    Vector2f otherPosition = other.getPosition();
    Vector2f otherHalfSize = other.getHalfSize();
    Vector2f thisPosition = getPosition();
    Vector2f thisHalfSize = getHalfSize();
    CollisionSide side = C_NONE;

    float deltaX = otherPosition.x - thisPosition.x;
    float deltaY = otherPosition.y - thisPosition.y;
    float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
    float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

    if (intersectX < 0.0f && intersectY < 0.0f) {
        push = min(max(push, 0.0f), 1.0f);
        if (intersectX > intersectY) {
            if (deltaX > 0.0f) {
                move(intersectX * (1.0f - push), 0.0f);
                other.move(-intersectX * push, 0.0f);
                side = C_LEFT;
            } else {
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX * push, 0.0f);
                side = C_RIGHT;
            }
            m_vel.x = 0.0f;
            other.m_vel.x = 0.0f;
        } else {
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);
                side = C_TOP;
            } else {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);
                side = C_BOTTOM;
            }
            m_vel.y = 0.0f;
            other.m_vel.y = 0.0f;
        }
        return CollisionInfo(&other, side);
    }
    return CollisionInfo(&other, side);
}