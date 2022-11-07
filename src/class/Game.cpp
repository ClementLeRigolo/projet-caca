#include "class/Game.hpp"
#include "class/Asset.hpp"

Game::Game()
{
    m_render = new Render();
    Asset::loadAssets();
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

void Game::update()
{
    static float clock = 0;

    getTimer()->update();

    if (getTimer()->getSeconds() > clock + 0.2) {
        clock = getTimer()->getSeconds();
        getRender()->getCurrentScene()->getText()->setString("fps : " + to_string((int)getTimer()->getFps()));
    }

    pollEvents();
}
