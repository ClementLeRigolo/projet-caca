#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Game::Game()
{
    m_render = new Render();
    Asset::loadAssets();
    Collection::loadCollection();
}

bool Game::isRunning() const { return m_render->getWindow()->isOpen(); }

Render* Game::getRender() { return m_render; }

Timer* Game::getTimer() { return &m_timer; }

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

    if (getTimer()->getSeconds() > clock + 0.15) {
        clock = getTimer()->getSeconds();
        getRender()->getCurrentScene()->getText()->setString("fps : " + to_string((int)getTimer()->getFps()));
    }
}

void Game::update()
{
    getTimer()->update();
    updateFpsIndicator();
    pollEvents();
}
