#include "class/Game.hpp"

Game::Game()
{
    m_render = new Render();
}

bool Game::isRunning() const { return m_render->window->isOpen(); }

Render* Game::getRender() const { return m_render; }

void Game::pollEvents()
{
    while (m_render->window->pollEvent(m_event)) {
        switch (m_event.type) {
            case Event::Closed:
                m_render->window->close();
                break;
        }
    }
}

void Game::update()
{
    pollEvents();
}
