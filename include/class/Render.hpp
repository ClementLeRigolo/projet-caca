#pragma once

#include "class/Scene.hpp"

class Render
{
    private:
        RenderWindow m_window;
        Scene* m_currentScene;

    public:
        Render();
        void init(Scene* scene);
        RenderWindow* getWindow();
        Scene* getCurrentScene();
        void setCurrentScene(Scene* scene);
        void update();
};
