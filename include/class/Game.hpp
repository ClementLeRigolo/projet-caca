#pragma once

#include "class/Render.hpp"

class Game
{
    private:
        Render* m_render;
        Event m_event;

    public:
        Game();
        bool isRunning() const;
        Render* getRender() const;
        void pollEvents();
        void update();
};
