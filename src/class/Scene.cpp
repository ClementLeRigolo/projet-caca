#include "class/Scene.hpp"
#include "class/Asset.hpp"

Scene::Scene() : m_index(0) {
    m_text.setFont(Asset::FONT);
}

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

Text* Scene::getText() { return &m_text; };

RectangleShape* Scene::getBackground() { return &m_background; }

void Scene::setBackground(RectangleShape background) { m_background = background; }

RectangleShape* Scene::getForeground() { return &m_foreground; }

void Scene::setForeground(RectangleShape foreground) { m_foreground = foreground; }

void Scene::display(RenderWindow* window)
{
    window->draw(m_text);
    window->draw(m_background);
    window->draw(m_foreground);
}