#include "class/system/Scene.hpp"
#include "class/Game.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

Scene::Scene()
{
    reloadScene();
}

void Scene::reloadScene()
{
    m_view.setSize(SCREEN_SIZE);
    m_view.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_fpsText.setFont(GET_FONT(DEBUG_FONT));
    m_fpsText.setPosition(Vector2f(0, 0));
    m_hasFocus = false;

    setMusic(Game::getInstance().getMusic());
}

void Scene::setMusic(Music* music) { m_music = music; }

Music* Scene::getMusic() { return m_music; }

int Scene::getIndex() const { return m_index; }

void Scene::setIndex(int index) { m_index = index; }

RectangleShape& Scene::getBackground() { return m_background; }

void Scene::setBackground(RectangleShape background) { m_background = background; }

RectangleShape& Scene::getForeground() { return m_foreground; }

void Scene::setForeground(RectangleShape foreground) { m_foreground = foreground; }

View& Scene::getView() { return m_view; }

void Scene::setView(View view) { m_view = view; }

Text& Scene::getText() { return m_fpsText; };

bool Scene::hasFocus()
{
    return m_hasFocus;
}

void Scene::setFocus(bool boolean)
{
    m_hasFocus = boolean;
}

void Scene::pollEvents(RenderWindow& window)
{
}

void Scene::updateLogic(RenderWindow& window)
{
    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
}

void Scene::display(RenderWindow& window)
{
    window.setView(m_view);
    window.draw(m_background);
    window.draw(m_foreground);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}