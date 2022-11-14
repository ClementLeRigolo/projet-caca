#pragma once

#include "class/Render.hpp"
#include "class/Timer.hpp"
#include "class/Entity.hpp"

class Game
{
    private:
        Game();
        static Game s_instance;
        Render* m_render;
        Scene* m_currentScene;
        Event m_event;
        Player m_player;
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();

    public:
        static Game& getInstance();
        bool isRunning() const;
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene);
        void pollEvents();
        Render* getRender();
        Player& getPlayer();
        Event& getEvent();
        void update();
        void render();
};
