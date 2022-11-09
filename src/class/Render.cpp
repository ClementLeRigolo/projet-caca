#include "class/Render.hpp"
#include "class/Collection.hpp"

Render::Render()
{
    m_window.create(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), WINDOW_NAME, Style::Default);
    m_currentScene = &Collection::MAIN_MENU;
}

Render::~Render()
{
    m_currentScene->~Scene();
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
