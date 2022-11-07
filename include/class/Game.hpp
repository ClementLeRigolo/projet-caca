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
        Render* getRender();
        Timer* getTimer();
        void pollEvents();
        void update();
};
