#include "class/Render.hpp"
#include "class/Collection.hpp"

Render::Render()
{
    window = new RenderWindow(VideoMode(960, 540, 32), WINDOW_NAME, Style::Default);
    m_currentScene = &Collection::LEVEL_1;
}

Render::~Render()
{
    delete window;
    m_currentScene->~Scene();
}

Scene* Render::getCurrentScene() const { return m_currentScene; }

void Render::setCurrentScene(Scene* scene) { m_currentScene = scene; }

void Render::update()
{
    window->clear();
    m_currentScene->display(window);
    window->display();
}
