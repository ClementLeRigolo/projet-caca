#pragma once

#include "class/Entity.hpp"

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
        View m_view;
        states_t m_states;

    public:
        Player();
        void control();
        void update(Level *level);
        void updateStates();
        void setHealth(float health);
        void viewFollow();
        View& getView();
        float getHealth() const;
};