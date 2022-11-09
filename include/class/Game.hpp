#pragma once

#include "class/Render.hpp"
#include "class/Timer.hpp"

class Game
{
    private:
        Render* m_render;
        Scene* m_currentScene;
        Event m_event;
    
    private:
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();

    public:
        Game();
        static Game* instance;
        bool isRunning() const;
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene);
        Render* getRender();
        void pollEvents();
        void update();
        void render();
};
