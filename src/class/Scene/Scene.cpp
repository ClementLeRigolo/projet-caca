#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

Scene::Scene() {
    Asset::loadAssets();
    m_view.setSize(SCREEN_SIZE);
    m_view.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_fpsText.setFont(Asset::FONT);
    m_fpsText.setPosition(Vector2f(0, 0));
}

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

RectangleShape& Scene::getBackground() { return m_background; }

void Scene::setBackground(RectangleShape background) { m_background = background; }

RectangleShape& Scene::getForeground() { return m_foreground; }

void Scene::setForeground(RectangleShape foreground) { m_foreground = foreground; }

View& Scene::getView() { return m_view; }

void Scene::setView(View view) { m_view = view; }

Text& Scene::getText() { return m_fpsText; };

void Scene::updateLogic(RenderWindow& window)
{
}

void Scene::display(RenderWindow& window)
{
    window.setView(m_view);
    window.draw(m_background);
    window.draw(m_foreground);
    window.draw(m_fpsText);
}