#include "class/Entity.hpp"
#include "class/system/Timer.hpp"
#include "class/Game.hpp"

Entity::Entity()
{
    getCollider().m_acc = Vector2f(0, 0);
    getCollider().m_vel = Vector2f(0, 0);
    getCollider().setPosition(Vector2f(480, 270));
    m_sprite.setColor(Color::White);
    m_sprite.setPosition(getCollider().getPosition());
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitboxVisible = false;
    m_speed = 20;
}

Entity::Entity(Vector2f pos)
{
    getCollider().m_acc = Vector2f(0, 0);
    getCollider().m_vel = Vector2f(0, 0);
    getCollider().setPosition(pos);
    m_sprite.setTexture(GET_TEXTURE(ENTITY_TEXTURE), true);
    m_sprite.setOrigin(getCenter(GET_TEXTURE(ENTITY_TEXTURE)));
    m_sprite.setColor(Color::White);
    m_sprite.setPosition(getCollider().getPosition());
    m_sprite.setScale(0.3, 0.3);
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    setHitboxVisible(true);
    m_speed = 20;
}

Entity::Entity(Texture* texture, Vector2f scale)
{
    getCollider().m_acc = Vector2f(0, 0);
    getCollider().m_vel = Vector2f(0, 0);
    getCollider().setPosition(480, 270);
    m_sprite.setColor(Color::White);
    m_sprite.setTexture(*texture, true);
    m_sprite.setOrigin(getCenter(*texture));
    m_sprite.setScale(scale);
    m_sprite.setPosition(getCollider().getPosition());
    m_hitbox.setScale(scale);
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitboxVisible = false;
    m_speed = 20;
}

void Entity::setSpeed(float speed) { m_speed = speed; }

Vector2f Entity::getSize() const
{
    return Vector2f(m_hitbox.getGlobalBounds().width,
    m_hitbox.getGlobalBounds().height);
}

void Entity::setTexture(Texture* texture)
{
    m_sprite.setTexture(*texture, true);
    m_sprite.setOrigin(getCenter(*texture));
}

void Entity::setScale(Vector2f scale)
{
    m_sprite.setScale(scale);
    m_hitbox.setScale(scale);
}

void Entity::setHitboxSize(Vector2f size, bool recenter)
{
    m_hitbox.setSize(size);
    if (!recenter)
        return;
    m_hitbox.setOrigin(m_hitbox.getSize().x / 2.0, m_hitbox.getSize().y / 2.0);
}

void Entity::setSpriteOffset(Vector2f offset)
{
    m_sprite.setOrigin((m_sprite.getGlobalBounds().width / 2.0) + offset.x,
    (m_sprite.getGlobalBounds().height/ 2.0) + offset.y);
}

Sprite& Entity::getSprite() { return m_sprite; }

Collider& Entity::getCollider() { return m_hitbox; }

void Entity::setHitboxVisible(bool visible)
{
    m_hitboxVisible = visible;
}

float Entity::getSpeed() const { return m_speed; }

Vector2f Entity::getPosition()
{
    return getCollider().getPosition();
}

bool Entity::isHitboxVisible() const { return m_hitboxVisible; };

void Entity::draw(sf::RenderTarget &target)
{
    target.draw(m_sprite);
    if (m_hitboxVisible)
        target.draw(m_hitbox);
}

void Entity::reposition()
{
    getCollider().m_acc *= Timer::getFrameDelta();
    getCollider().m_vel += vectMult(getCollider().m_acc, 500.0);
    getCollider().move(getCollider().m_vel * Timer::getFrameDelta());
    getCollider().m_vel.x = damp(getCollider().m_vel.x, 0.001f, Timer::getFrameDelta());
    getCollider().m_vel.y = damp(getCollider().m_vel.y, 0.05f, Timer::getFrameDelta());
    getCollider().m_acc = Vector2f(0, 0);
    getCollider().m_acc.y += 2 * GRAVITY;
    m_sprite.setPosition(getCollider().getPosition());
    m_hitbox.setPosition(getCollider().getPosition());
}

void Entity::update()
{
    reposition();
};