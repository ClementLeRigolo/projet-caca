#pragma once

#include "class/Render.hpp"
#include "class/Timer.hpp"

class Game
{
    private:
        Game();
        static Game s_instance; 
        Render* m_render;
        Scene* m_currentScene;
        Event m_event;
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();

    public:
        static Game& getInstance();
        bool isRunning() const;
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene);
        Render* getRender();
        void pollEvents();
        void update();
        void render();
};
