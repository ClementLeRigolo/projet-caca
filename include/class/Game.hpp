#pragma once

#include "class/graphic/Render.hpp"
#include "class/system/Scene.hpp"
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
        Music* m_music;
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();

    public:
        static Game& getInstance();
        bool isRunning() const;
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene);
        void pollEvents();
        void setMusic(Music* music);
        Music* getMusic();
        Render* getRender();
        Player& getPlayer();
        Event& getEvent();
        void update();
        void render();
        void Initialize();
};
