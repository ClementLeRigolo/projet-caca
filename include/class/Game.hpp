#pragma once

#include "class/graphic/Render.hpp"
#include "class/system/Scene.hpp"
#include "class/Entity.hpp"
#include "enum/Scenes.hpp"
#include "class/AssetManager.hpp"

#define GET_TEXTURE(TextureID) Game::getInstance().getAssetManager().getTexture(TextureID)
#define GET_SOUND(SoundID) Game::getInstance().getAssetManager().getSound(SoundID)
#define GET_FONT(FontID) Game::getInstance().getAssetManager().getFont(FontID)

class Game
{
    private:
        Game();
        AssetManager m_assetManager;
        static Game s_instance;
        Render* m_render;
        Scene* m_currentScene;
        map<SceneID, unique_ptr<Scene>> m_scenes;
        Event m_event;
        Player m_player;
        Music* m_music;
        void updateSceneLogic(Scene* scene);
        void updateFpsIndicator();
        void printCoordsOnClick();

    public:
        void addScene(SceneID identifier, unique_ptr<Scene> scene);
        Scene& getScene(SceneID identifier);
        AssetManager& getAssetManager();
        static Game& getInstance();
        bool isRunning() const;
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene, bool reloadScene);
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

