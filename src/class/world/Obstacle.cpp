#include "class/world/Obstacle.hpp"

Obstacle::Obstacle(Vector2f pos, Vector2f size)
{
    m_shape.setSize(size);
    m_shape.setOrigin(getCenter(m_shape));
    m_shape.setPosition(pos);
}

Collider& Obstacle::getCollider()
{
    return m_shape;
}

RectangleShape& Obstacle::getShape()
{
    return m_shape;
}
