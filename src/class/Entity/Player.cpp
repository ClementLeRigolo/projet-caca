#include "class/Entity.hpp"
#include "class/Asset.hpp"
#include "class/Timer.hpp"

Player::Player()
{
    setTexture(&Asset::ENTITY_TEXTURE);
    setScale(Vector2f(0.4, 0.4));
    getHitbox()->setOutlineThickness(2);
    setHitboxSize(Vector2f(300, 400), true);
    setHitboxOffset(Vector2f(0, 0));
    setHitboxVisible(true);
    setHealth(10);
    setSpeed(8);
    m_states.falling = false;
    m_states.grounded = false;
    m_states.idle = false;
    m_states.jumping = false;
    m_states.running = false;
}

Player* Player::instance;

void Player::setHealth(float health)
{
    m_health = health;
}

float Player::getHealth() const { return m_health; }

void Player::control()
{
    if (Keyboard::isKeyPressed(Keyboard::Z))
        m_acc.y = -getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::S))
        m_acc.y = getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::D))
        m_acc.x = getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::Q))
        m_acc.x = -getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::Space) && !m_states.jumping) {
        m_states.jumping = true;
        m_acc.y = 0;
        m_vel.y = -40.0 * Timer::getFrameDelta() * 100.0;
    }
}

void Player::updateStates()
{
    if (m_states.jumping && m_vel.y >= 0)
        m_states.jumping = false;
}

void Player::update()
{
    control();
    updateStates();
    reposition();
}