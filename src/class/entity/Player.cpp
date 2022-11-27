#include "class/Entity.hpp"
#include "class/Game.hpp"
#include "class/system/Timer.hpp"

Player::Player()
{
    m_view.setSize(SCREEN_SIZE);
    m_view.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_view.zoom(0.9);
    setTexture(&GET_TEXTURE(ENTITY_TEXTURE));
    setScale(Vector2f(0.4, 0.4));
    getCollider().setOutlineThickness(2);
    setHitboxSize(Vector2f(300, 400), true);
    setHitboxVisible(true);
    setHealth(10);
    setSpeed(15);
    m_states.falling = false;
    m_states.grounded = false;
    m_states.idle = false;
    m_states.jumping = false;
    m_states.running = false;
}

void Player::setHealth(float health) { m_health = health; }

float Player::getHealth() const { return m_health; }

void Player::control()
{
    if (Keyboard::isKeyPressed(Keyboard::Z))
        getCollider().m_acc.y += -getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::S))
        getCollider().m_acc.y += getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::D))
        getCollider().m_acc.x += getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::Q))
        getCollider().m_acc.x += -getSpeed();
    if (Keyboard::isKeyPressed(Keyboard::Space) && !m_states.jumping) {
        m_states.jumping = true;
        getCollider().m_vel.y = -4000;
    }
}

View& Player::getView() { return m_view; }

void Player::viewFollow()
{
    Vector2f target = Player::getPosition();
    target.y -= Player::getSize().y;
    Vector2f sign = Vector2f(1, 1);
    Vector2f diff = vectSub(target, m_view.getCenter());
    Vector2f pos = vectMult(diff, 9.0 * Timer::getFrameDelta());
    m_view.setCenter(m_view.getCenter() + pos);
}

void Player::updateStates()
{
    if (m_states.jumping && getCollider().m_vel.y >= 0)
        m_states.jumping = false;
}

void Player::update()
{
    control();
    updateStates();
    reposition();
}