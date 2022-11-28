#include "class/Entity.hpp"
#include "class/Game.hpp"
#include "class/system/Timer.hpp"

Player::Player()
{
    m_currentTexture = IDLE;
    m_view.setSize(SCREEN_SIZE);
    m_view.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_view.zoom(0.9);
    getCollider().setOutlineThickness(2);
    getSprite().init(GET_TEXTURE(P_IDLE), 4, 2, true);
    getSprite().setScale(Vector2f(4, 4));
    setHitboxSize(Vector2f(120, 200), true);
    setHitboxVisible(false);
    setHealth(10);
    setSpeed(15);
    m_states.falling = false;
    m_states.grounded = false;
    m_states.idle = true;
    m_states.jumping = false;
    m_states.running = false;
    m_states.canJump = true;
    m_states.wallJumping = false;
    m_states.wallSliding = false;
}

void Player::setHealth(float health) { m_health = health; }

float Player::getHealth() const { return m_health; }

void Player::control()
{
    if (!m_states.grounded)
        getCollider().m_friction = 0.5;
    else
        getCollider().m_friction = 0.0003;

    if (Keyboard::isKeyPressed(Keyboard::D) && !m_states.wallJumping) {
        getCollider().m_acc.x += getSpeed();
        getCollider().m_friction = 0.0003;
    }
    if (Keyboard::isKeyPressed(Keyboard::Q) && !m_states.wallJumping) {
        getCollider().m_acc.x += -getSpeed();
        getCollider().m_friction = 0.0003;
    }
    if (Keyboard::isKeyPressed(Keyboard::Space) &&
        !m_states.jumping && m_states.canJump && !m_states.wallJumping) {
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

void Player::updateStates(CollisionInfo info)
{
    static float lastPosY = getCollider().getPosition().y;

    if (info.getSide() == Collision::BOTTOM) {
        m_states.jumping = false;
        m_states.canJump = true;
        m_states.falling = false;
        m_states.grounded = true;
        m_states.hanging = false;
        m_states.wallJumping = false;
    } else if (lastPosY < getCollider().getPosition().y) {
        m_states.falling = true;
        m_states.grounded = false;
        m_states.canJump = false;
    }

    if (m_states.grounded && abs(getCollider().m_vel.x) < 150 && abs(getCollider().m_vel.y == 0))
        m_states.idle = true;
    else
        m_states.idle = false;

    if (m_states.grounded && abs(getCollider().m_vel.x) > 150 && abs(getCollider().m_vel.y == 0)) {
        m_states.running = true;
    } else {
        m_states.running = false;
    }

    if (m_states.falling || m_states.hanging) {
        if ((info.getSide() == Collision::LEFT
            || info.getSide() == Collision::RIGHT)
            && (Keyboard::isKeyPressed(Keyboard::D)
            || Keyboard::isKeyPressed(Keyboard::Q))
            && (abs((info.getShape()->getGlobalBounds().top - getCollider().getGlobalBounds().top))) < 10
            && abs(getCollider().m_vel.x) == 0) {
            m_states.hanging = true;
        } else if ((!Keyboard::isKeyPressed(Keyboard::D)
            && !Keyboard::isKeyPressed(Keyboard::Q))
            || abs(getCollider().m_vel.x) != 0)
            m_states.hanging = false;
    }

    if (getCollider().m_vel.y > 0) {
        m_states.falling = true;
        m_states.jumping = false;
    }

    if (m_states.jumping) {
        m_states.hanging = false;
        m_states.falling = false;
    }

    if (m_states.hanging) {
        Vector2f origin = getCenter(getSprite());
        getSprite().setOrigin(origin.x - 7, origin.y - 3);
        m_states.canJump = true;
        m_states.wallJumping = false;
        m_states.wallSliding = false;
        m_states.jumping = false;
        m_states.falling = false;
        getCollider().m_vel.y = 0;
        getCollider().setGravityEnabled(false);
    } else
        getCollider().setGravityEnabled(true);

    if (!m_states.hanging && !m_states.grounded && !m_states.jumping
        && ((info.getSide() == Collision::LEFT && Keyboard::isKeyPressed(Keyboard::Q))
        || info.getSide() == Collision::RIGHT && Keyboard::isKeyPressed(Keyboard::D))) {
        getCollider().setGravityMultiplier(0.1);
        m_states.wallJumping = false;
        m_states.wallSliding = true;
        m_states.falling = false;
        Vector2f origin = getCenter(getSprite());
        getSprite().setOrigin(origin.x - 7, origin.y - 3);
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            m_states.jumping = true;
            m_states.wallSliding = false;
            m_states.wallJumping = true;
            if (info.getSide() == Collision::LEFT)
                getCollider().m_vel.x = 1000;
            if (info.getSide() == Collision::RIGHT)
                getCollider().m_vel.x = -1000;
            getCollider().m_vel.y -= 3000;
        }
    } else {
        m_states.wallSliding = false;
        getCollider().setGravityMultiplier(1.0f);
    }

    lastPosY = getCollider().getPosition().y;
    updateTexture();
}

void Player::updateTexture()
{
    if (m_states.idle && m_currentTexture != IDLE) {
        //cout << "idle" << endl;
        getSprite().init(GET_TEXTURE(P_IDLE), 4, 2, true);
        m_currentTexture = IDLE;
        return;
    }

    if (m_states.running && m_currentTexture != RUN) {
        //cout << "running" << endl;
        getSprite().init(GET_TEXTURE(P_RUN), 4, 2, true);
        m_currentTexture = RUN;
        return;
    }

    if (m_states.jumping && m_currentTexture != JUMP) {
        //cout << "jump" << endl;
        getSprite().init(GET_TEXTURE(P_JUMP), 2, 2, false);
        m_currentTexture = JUMP;
        return;
    }

    if (m_states.falling && m_currentTexture != FALL) {
        //cout << "falling" << endl;
        getSprite().init(GET_TEXTURE(P_FALL), 4, 2, false);
        m_currentTexture = FALL;
        return;
    }

    if ((m_states.wallSliding || m_states.hanging) && m_currentTexture != HANG) {
        //cout << "hanging" << endl;
        getSprite().init(GET_TEXTURE(P_HANG), 4, 2, false);
        m_currentTexture = HANG;
        return;
    }
}

void Player::update()
{
    getSprite().update();
    control();
    reposition();
}