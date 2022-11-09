#include "class/Entity.hpp"
#include "class/Timer.hpp"

Entity::Entity(Texture* texture, Vector2f scale)
{
    m_acc = Vector2f(0, 0);
    m_vel = Vector2f(0, 0);
    m_pos = Vector2f(480, 270);
    m_sprite.setColor(Color::White);
    m_sprite.setTexture(*texture, true);
    m_sprite.setOrigin(getCenter(*texture));
    m_sprite.setScale(scale);
    m_sprite.setPosition(m_pos);
    m_hitbox.setTexture(texture);
    m_hitbox.setScale(scale);
    m_hitbox.setFillColor(Color::Transparent);
    m_hitbox.setSize(Vector2f(20, 20));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 100));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitbox.setPosition(m_pos);
    m_health = 10;
    m_speed = 20;
}

void Entity::setPos(Vector2f pos)
{
    m_pos = pos;
}

void Entity::setSpeed(float speed)
{
    m_speed = speed;
}

void Entity::setTexture(Texture* texture)
{
    m_sprite.setTexture(*texture, true);
    m_sprite.setOrigin(getCenter(*texture));
}

void Entity::setHealth(float health)
{
    m_health = health;
}

void Entity::setScale(Vector2f scale)
{
    m_sprite.setScale(scale);
    m_hitbox.setScale(scale);
}

void Entity::setHitboxSize(Vector2f size)
{
    m_hitbox.setSize(size);
    m_hitbox.setOrigin(m_hitbox.getSize().x / 2.0, m_hitbox.getSize().y / 2.0);
}

void Entity::setHitboxOffset(Vector2f offset)
{
    m_hitbox.setPosition(Vector2f(m_pos.x + offset.x, m_pos.y + offset.y));
}

Sprite* Entity::getSprite()
{
    return &m_sprite;
}

RectangleShape* Entity::getHitbox()
{
    return &m_hitbox;
}

void Entity::draw(sf::RenderTarget &target)
{
    target.draw(m_hitbox);
    target.draw(m_sprite);
}

void Entity::update(float deltaTime)
{
    m_vel += m_acc;
    m_pos += m_vel;
    m_sprite.setPosition(m_pos);
    m_hitbox.setPosition(m_pos);
};