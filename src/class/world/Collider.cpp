#include "class/Collider.hpp"
#include <iostream>

CollisionInfo::CollisionInfo()
{
    m_side = Collision::NONE;
    m_shape = NULL;
}

CollisionInfo::CollisionInfo(const RectangleShape* shape, Collision::Side side)
{
    m_shape = shape;
    m_side = side;
}

float Collider::getGravityMultiplier() { return m_gravityMultiplier; }

void Collider::setGravityMultiplier(float multiplier) { m_gravityMultiplier = multiplier; }

const RectangleShape* CollisionInfo::getShape() { return m_shape; }

Collision::Side CollisionInfo::getSide() { return m_side; }

void Collider::setGravityEnabled(bool toggle) { m_gravityEnabled = toggle; }

bool Collider::isGravityEnabled() { return m_gravityEnabled; }

Vector2f Collider::getHalfSize() { return Vector2f(getGlobalBounds().width / 2.0, getGlobalBounds().height / 2.0); }

Collider::Collider(const RectangleShape& shape)
{
    m_acc = Vector2f(0.0f, 0.0f);
    m_vel = Vector2f(0.0f, 0.0f);
    m_friction = 0.0003;
    m_gravityEnabled = true;
    setGravityMultiplier(1);

    setFillColor(shape.getFillColor());
    this->setOrigin(shape.getOrigin());
    this->setOutlineColor(shape.getOutlineColor());
    this->setOutlineThickness(shape.getOutlineThickness());
    this->setPosition(shape.getPosition());
    this->setRotation(shape.getRotation());
    this->setScale(shape.getScale());
    this->setSize(shape.getSize());
    this->setTexture(shape.getTexture());
    this->setTextureRect(shape.getTextureRect());
}

Collider::Collider()
{
    m_acc = Vector2f(0.0f, 0.0f);
    m_vel = Vector2f(0.0f, 0.0f);
    m_friction = 0.0003;
    m_gravityEnabled = true;
    setGravityMultiplier(1);
}

Collider::Collider(const sf::Texture* texture, sf::Vector2f pos, sf::Vector2f size)
{
    setSize(size);
    setTextureRect(IntRect(0, 0, size.x, size.y));
    setTexture(texture);
    setOrigin(getCenter(*this));
    setPosition(pos);
    setTextureRect(IntRect((-getSize().x / 2.0) + getPosition().x,
    (-getSize().y / 2.0) + getPosition().y, getSize().x, getSize().y));
}

CollisionInfo Collider::checkCollision(Collider& other, float push)
{
    Vector2f otherPosition;
    otherPosition.x = other.getGlobalBounds().left + other.getGlobalBounds().width * 0.5;
    otherPosition.y = other.getGlobalBounds().top + other.getGlobalBounds().height * 0.5;
    Vector2f otherHalfSize = other.getHalfSize();
    Vector2f thisPosition;
    thisPosition.x = getGlobalBounds().left + getGlobalBounds().width * 0.5;
    thisPosition.y = getGlobalBounds().top + getGlobalBounds().height * 0.5;
    Vector2f thisHalfSize = getHalfSize();
    Collision::Side side = Collision::NONE;

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
                side = Collision::LEFT;
            } else {
                move(-intersectX * (1.0f - push), 0.0f);
                other.move(intersectX * push, 0.0f);
                side = Collision::RIGHT;
            }
            m_vel.x = 0.0f;
            other.m_vel.x = 0.0f;
        } else {
            if (deltaY > 0.0f) {
                move(0.0f, intersectY * (1.0f - push));
                other.move(0.0f, -intersectY * push);
                side = Collision::TOP;
            } else {
                move(0.0f, -intersectY * (1.0f - push));
                other.move(0.0f, intersectY * push);
                side = Collision::BOTTOM;
            }
            m_vel.y = 0.0f;
            other.m_vel.y = 0.0f;
        }
        return CollisionInfo(&*this, side);
    }
    return CollisionInfo(&*this, side);
}