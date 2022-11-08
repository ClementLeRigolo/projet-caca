#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Scene::Scene() : m_index(0) {
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

void Scene::display(RenderWindow* window)
{
    window->draw(m_background);
    window->draw(m_foreground);
    window->setView(m_view);
    Collection::TEST_ENTITY.setTexture(&Asset::TEST_TEXTURE);
    window->draw(Collection::TEST_ENTITY.getSprite());
    window->draw(Collection::TEST_ENTITY.getHitbox());
    
    window->draw(m_text);
}