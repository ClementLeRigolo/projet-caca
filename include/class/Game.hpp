#pragma once

#include "class/Render.hpp"
#include "class/Timer.hpp"

class Game
{
    private:
        Render* m_render;
        Event m_event;
        Timer m_timer;

    public:
        Game();
        bool isRunning() const;
        Render* getRender() const;
        Timer* getTimer();
        void pollEvents();
        void update();
};
