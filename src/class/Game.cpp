#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"

Game::Game()
{
    Asset::loadAssets();
    Collection::loadCollection();
    Timer::start();
    m_render = new Render();
    m_currentScene = &Collection::MAIN_MENU;
    m_player = Player();
}

Game Game::s_instance;

Game& Game::getInstance() { return s_instance; }

bool Game::isRunning() const { return m_render->getWindow().isOpen(); }

Render* Game::getRender() { return m_render; }

Scene* Game::getCurrentScene() { return m_currentScene; }

void Game::setCurrentScene(Scene* scene) { m_currentScene = scene; }

Event& Game::getEvent()
{
    return m_event;
}

Player& Game::getPlayer() { return m_player; }

void Game::updateFpsIndicator()
{
    static float clock = 0;

    if (Timer::getSeconds() > clock + 0.15) {
        clock = Timer::getSeconds();
        m_currentScene->getText().setString("fps : " + \
        to_string((int)Timer::getFps()));
    }
}

void Game::updateSceneLogic(Scene* scene)
{
    // Updates scene logic
    scene->pollEvents(getRender()->getWindow());
    scene->updateLogic(getRender()->getWindow());
}

void Game::update()
{
    Timer::update();
    updateFpsIndicator();
    updateSceneLogic(m_currentScene);
}

void Game::render()
{
    m_render->getWindow().clear();
    m_currentScene->display(getRender()->getWindow());
    m_render->getWindow().display();
}
