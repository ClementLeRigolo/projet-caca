#include "class/Render.hpp"
#include "class/Collection.hpp"

Render::Render()
{
    m_window.create(VideoMode(960, 540, 32), WINDOW_NAME, Style::Default);
    m_currentScene = &Collection::LEVEL_1;
}

Render::~Render()
{
    delete m_currentScene;
}

RenderWindow* Render::getWindow() { return &m_window; }

Scene* Render::getCurrentScene() { return m_currentScene; }

void Render::setCurrentScene(Scene* scene) { m_currentScene = scene; }

void Render::update()
{
    m_window.clear();
    m_currentScene->display(&m_window);
    m_window.display();
}
