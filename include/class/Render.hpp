#pragma once

#include "class/Scene.hpp"

class Render
{
    private:
        Scene* m_currentScene;

    public:
        Render();
        ~Render();
        RenderWindow* window;
        Scene* getCurrentScene() const;
        void setCurrentScene(Scene* scene);
        void update();
};
