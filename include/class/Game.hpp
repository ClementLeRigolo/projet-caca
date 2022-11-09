#pragma once

#include "class/Render.hpp"
#include "class/Timer.hpp"

class Game
{
    private:
        Render* m_render;
        Event m_event;

    public:
        Game();
        static Game* instance;
        bool isRunning() const;
        Render* getRender();
        void pollEvents();
        void update();

    private:
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();
};
