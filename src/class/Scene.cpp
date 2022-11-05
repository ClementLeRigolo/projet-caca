#include "class/Scene.hpp"

Scene::Scene() : m_index(0) {}

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

RectangleShape Scene::getBackground() const { return m_background; }

void Scene::setBackground(RectangleShape background) { m_background = background; }

RectangleShape Scene::getForeground() const { return m_foreground; }

void Scene::setForeground(RectangleShape foreground) { m_foreground = foreground; }

void Scene::display(RenderWindow* window)
{
    window->draw(m_background);
    window->draw(m_foreground);
}