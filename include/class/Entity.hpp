#pragma once

#include "libs.hpp"

class Entity {
    private:
        Sprite m_sprite;
        RectangleShape m_hitbox;
        float m_speed;
        float m_health;
        Vector2f m_vel;
        Vector2f m_pos;
        Vector2f m_acc;

    public:
        Entity(Texture texture, Vector2f scale);
        void setTexture(Texture *texture);
        void setHitboxSize(Vector2f size);
        void setHitboxOffset(Vector2f offset);
        void setPos(Vector2f pos);
        void setScale(Vector2f scale);
        void setHealth(float health);
        void setSpeed(float speed);
        Sprite getSprite();
        RectangleShape getHitbox();
        void update();
        void draw(sf::RenderTarget &target);
};
