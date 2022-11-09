#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Game::Game()
{
    Asset::loadAssets();
    Collection::loadCollection();
    Timer::start();
    m_render = new Render();
}

Game* Game::instance;

bool Game::isRunning() const { return m_render->getWindow()->isOpen(); }

Render* Game::getRender() { return m_render; }

void Game::pollEvents()
{
    while (m_render->getWindow()->pollEvent(m_event)) {
        switch (m_event.type) {
            case Event::Closed:
                m_render->getWindow()->close();
                break;
        }
    }
}

void Game::updateFpsIndicator()
{
    static float clock = 0;

    if (Timer::getSeconds() > clock + 0.15) {
        clock = Timer::getSeconds();
        getRender()->getCurrentScene()->getText()->setString("fps : " + \
        to_string((int)Timer::getFps()));
    }
}

void Game::updateSceneLogic(Scene* scene)
{
    // Updates scene logic
    scene->updateLogic(getRender()->getWindow());
}

void Game::update()
{
    Timer::update();
    updateFpsIndicator();
    updateSceneLogic(getRender()->getCurrentScene());
    pollEvents();
}
