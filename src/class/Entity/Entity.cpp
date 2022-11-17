#include "class/Entity.hpp"
#include "class/Timer.hpp"
#include "class/AssetManager.hpp"

Entity::Entity()
{
    m_acc = Vector2f(0, 0);
    m_vel = Vector2f(0, 0);
    m_pos = Vector2f(480, 270);
    m_sprite.setColor(Color::White);
    m_sprite.setPosition(m_pos);
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitbox.setPosition(m_pos);
    m_hitboxVisible = false;
    m_speed = 20;
}

Entity::Entity(Vector2f pos)
{
    m_acc = Vector2f(0, 0);
    m_vel = Vector2f(0, 0);
    m_pos = pos;
    m_sprite.setTexture(GET_TEXTURE(ENTITY_TEXTURE), true);
    m_sprite.setOrigin(getCenter(GET_TEXTURE(ENTITY_TEXTURE)));
    m_sprite.setColor(Color::White);
    m_sprite.setPosition(m_pos);
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitbox.setPosition(m_pos);
    m_hitboxVisible = false;
    m_speed = 20;
}

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
    m_hitbox.setScale(scale);
    m_hitbox.setFillColor(Color(255, 0, 0, 100));
    m_hitbox.setSize(Vector2f(100, 100));
    m_hitbox.setOutlineThickness(1);
    m_hitbox.setOutlineColor(Color(255, 0, 0, 200));
    m_hitbox.setOrigin(getCenter(m_hitbox));
    m_hitbox.setPosition(m_pos);
    m_hitboxVisible = false;
    m_speed = 20;
}

void Entity::setPos(Vector2f pos) { m_pos = pos; }

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

void Entity::setHitboxOffset(Vector2f offset)
{
    m_hitbox.setOrigin((m_hitbox.getSize().x / 2.0) + offset.x,
    (m_hitbox.getSize().y / 2.0) + offset.y);
}

Sprite& Entity::getSprite() { return m_sprite; }

RectangleShape& Entity::getHitbox() { return m_hitbox; }

void Entity::setHitboxVisible(bool visible)
{
    m_hitboxVisible = visible;
}

float Entity::getSpeed() const { return m_speed; }

Vector2f Entity::getPosition()
{
    FloatRect bound = m_hitbox.getGlobalBounds();

    return Vector2f(bound.left + (bound.width / 2.0),
    bound.top + (bound.height / 2.0));
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
    //m_acc = vectUnit(m_acc);
    m_acc *= Timer::getFrameDelta();
    m_vel += vectMult(m_acc, 500.0);
    m_pos += m_vel * Timer::getFrameDelta();
    if (m_pos.y > SCREEN_SIZE.y - getSize().y) {
        m_vel.y = 0;
        m_pos.y = SCREEN_SIZE.y - getSize().y;
    }
    m_vel.x = damp(m_vel.x, 0.001f, Timer::getFrameDelta());
    m_vel.y = damp(m_vel.y, 0.05f, Timer::getFrameDelta());
    m_acc = Vector2f(0, 0);
    m_acc.y += 2 * GRAVITY;
    m_sprite.setPosition(m_pos);
    m_hitbox.setPosition(m_pos);
}

void Entity::update()
{
    reposition();
};