#pragma once

#include "libs.hpp"

class Entity {
    protected:
        bool m_hitboxVisible;
        Sprite m_sprite;
        RectangleShape m_hitbox;
        float m_speed;
        Vector2f m_vel;
        Vector2f m_pos;
        Vector2f m_acc;

    public:
        Entity();
        Entity(Vector2f pos);
        Entity(Texture* texture, Vector2f scale);
        void setTexture(Texture* texture);
        void setHitboxVisible(bool visible);
        bool isHitboxVisible() const;
        void setHitboxSize(Vector2f size, bool recenter);
        void setHitboxOffset(Vector2f offset);
        void setPos(Vector2f pos);
        void setScale(Vector2f scale);
        void setSpeed(float speed);
        Vector2f getSize() const;
        float getSpeed() const;
        Sprite* getSprite();
        RectangleShape* getHitbox();
        virtual void update();
        virtual void reposition();
        virtual void draw(sf::RenderTarget &target);
};

class Player : public Entity
{
    private:
        float m_health;
        typedef struct states_s {
            bool idle;
            bool grounded;
            bool falling;
            bool jumping;
            bool running;
        } states_t;
        states_t m_states;

    public:
        Player();
        static Player* instance;
        void control();
        void update();
        void updateStates();
        void setHealth(float health);
        float getHealth() const;
};