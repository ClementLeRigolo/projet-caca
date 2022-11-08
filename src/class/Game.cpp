#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Game::Game()
{
    Asset::loadAssets();
    Collection::loadCollection();
    m_render = new Render();
}

Game* Game::instance;

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
    static float clock = 0;

    getTimer()->update();
    if (getTimer()->getSeconds() > clock + 0.5) {
        getRender()->getCurrentScene()->addEntity(Vector2f(randomNumber(0, 960), randomNumber(0, 540)));
        clock = getTimer()->getSeconds();
    }
    getRender()->getCurrentScene()->update(getRender()->getWindow());
    updateFpsIndicator();
    pollEvents();
}
