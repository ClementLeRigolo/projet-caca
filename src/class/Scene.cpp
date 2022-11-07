#include "class/Scene.hpp"

Scene::Scene() : m_index(0) {}

Scene::~Scene()
{
    delete m_background;
    delete m_foreground;
}

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

Text* Scene::getText() { return &m_text; };

RectangleShape* Scene::getBackground() const { return m_background; }

void Scene::setBackground(RectangleShape* background) { m_background = background; }

RectangleShape* Scene::getForeground() const { return m_foreground; }

void Scene::setForeground(RectangleShape* foreground) { m_foreground = foreground; }

void Scene::display(RenderWindow* window)
{
    Font font;

    font.loadFromFile("misc/font.ttf");

    m_text.setFont(font);
    window->draw(m_text);
    if (m_background != nullptr)
        window->draw(m_background[0]);
    if (m_foreground != nullptr)
        window->draw(m_foreground[0]);
}