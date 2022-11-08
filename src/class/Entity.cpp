#include "class/Entity.hpp"

Entity::Entity(Texture texture, Vector2f scale)
{
    m_acc = Vector2f(0, 0);
    m_vel = Vector2f(0, 0);
    m_pos = Vector2f(480, 270);
    m_sprite.setColor(Color::White);
    m_sprite.setTexture(texture, false);
    m_sprite.setOrigin(getTextureCenter(texture));
    m_sprite.setScale(scale);
    m_sprite.setPosition(m_pos);
    m_hitbox.setScale(scale);
    m_hitbox.setFillColor(Color::Transparent);
    m_hitbox.setSize(Vector2f(20, 20));
    m_hitbox.setFillColor(Color::White);
    m_hitbox.setTexture(&texture, true);
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 100));
    m_hitbox.setOrigin(m_hitbox.getSize().x / 2.0, m_hitbox.getSize().y / 2.0);
    m_hitbox.setPosition(m_pos);
    m_health = 10;
    m_speed = 3;
}

void Entity::setPos(Vector2f pos)
{
    m_pos = pos;
}

void Entity::setSpeed(float speed)
{
    m_speed = speed;
}

void Entity::setTexture(Texture *texture)
{
    m_sprite.setTexture(*texture, true);
    m_hitbox.setTexture(texture, true);
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
}

void Entity::setHitboxOffset(Vector2f offset)
{
    m_hitbox.setPosition(Vector2f(m_pos.x + offset.x, m_pos.y + offset.y));
}

Sprite Entity::getSprite()
{
    return m_sprite;
}

RectangleShape Entity::getHitbox()
{
    return m_hitbox;
}

void Entity::draw(sf::RenderTarget &target)
{
    target.draw(m_sprite);
    cout << m_pos.x << endl;
    cout << m_pos.y << endl;
}

void Entity::update()
{
};