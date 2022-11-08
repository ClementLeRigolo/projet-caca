#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Scene::Scene() {
    Asset::loadAssets();
    m_button.setTexture(&Asset::BUTTON_TEXTURE);
    m_button.getShape()->setSize(Vector2f(200, 100));
    m_button.setPos(Vector2f(300, 300));
    m_text.setFont(Asset::FONT);
}

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

RectangleShape* Scene::getBackground() { return &m_background; }

void Scene::setBackground(RectangleShape background) { m_background = background; }

RectangleShape* Scene::getForeground() { return &m_foreground; }

void Scene::setForeground(RectangleShape foreground) { m_foreground = foreground; }

View* Scene::getView() { return &m_view; }

void Scene::setView(View view) { m_view = view; }

Text* Scene::getText() { return &m_text; };

void Scene::addEntity(Vector2f pos)
{
    m_entities.push_back(new Entity(pos));
}

void Scene::update(RenderWindow* window)
{
    m_button.update(getMousePosition(window));
}

void Scene::display(RenderWindow* window)
{
    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i)->draw(*window);
    window->setView(m_view);
    window->draw(*m_button.getShape());
    window->draw(m_background);
    window->draw(m_foreground);
    window->draw(m_text);
}