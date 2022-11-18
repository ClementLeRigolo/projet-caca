#include "class/Game.hpp"
#include "class/Collection.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Settings.hpp"
#include "class/system/Timer.hpp"

Game::Game()
{
    Timer::start();

    addScene(INTRO_CREDITS, (unique_ptr<Scene>)(new MainMenu()));
    addScene(MAIN_MENU, (unique_ptr<Scene>)(new MainMenu()));
    addScene(SETTINGS_MENU, (unique_ptr<Scene>)(new SettingsMenu()));
    addScene(LEVEL_1, (unique_ptr<Scene>)(new Level()));

    m_render = new Render();
    m_currentScene = &getScene(MAIN_MENU);
    m_player = Player();
}

void Game::Initialize()
{
    Settings::GLOBAL_VOLUME = 100;
    Settings::SFX_VOLUME = 50;
    Settings::MUSIC_VOLUME = 50;
    getCurrentScene()->setMusic(m_music);
    if (getCurrentScene()->getMusic())
        getCurrentScene()->getMusic()->play();
}

void Game::addScene(SceneID identifier, unique_ptr<Scene> scene)
{
    auto insert = m_scenes.insert(make_pair(identifier, move(scene)));
    assert(insert.second);
}

Scene& Game::getScene(SceneID identifier)
{
    auto it = m_scenes.find(identifier);
    assert(it!= m_scenes.end());
    return *it->second;
}

Game Game::s_instance;

Music* Game::getMusic()
{
    return m_music;
}

void Game::setMusic(Music* music)
{
    m_music = music;
}

Game& Game::getInstance() { return s_instance; }

bool Game::isRunning() const { return m_render->getWindow().isOpen(); }

Render* Game::getRender() { return m_render; }

Scene* Game::getCurrentScene() { return m_currentScene; }

void Game::setCurrentScene(Scene* scene)
{
    RenderWindow& window = getRender()->getWindow();

    if (getCurrentScene()) {
        if (getCurrentScene()->getMusic())
            getCurrentScene()->getMusic()->stop();
        getCurrentScene()->setFocus(false);
    }
    scene->getView() = getLetterboxView(getCurrentScene()->getView(),
    window.getSize().x, window.getSize().y);
    scene->setMusic(m_music);
    if (scene->getMusic())
        scene->getMusic()->play();
    m_currentScene = scene;
}

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

void Game::pollEvents()
{
    Event &event = getEvent();
    Window& window = getRender()->getWindow();

    while (window.pollEvent(event)) {
        switch (event.type) {
            case Event::Resized:
                getCurrentScene()->getView() = getLetterboxView(getCurrentScene()->getView(),
                window.getSize().x, window.getSize().y);
                m_player.getView() = getLetterboxView(m_player.getView(),
                window.getSize().x, window.getSize().y);
                break;
            case Event::Closed:
                window.close();
                break;
            default:
                getCurrentScene()->pollEvents(getRender()->getWindow());
        }
    }
}

void Game::updateSceneLogic(Scene* scene)
{
    // Updates scene logic
    scene->updateLogic(getRender()->getWindow());
    if (scene->getMusic())
        scene->getMusic()->setVolume(Settings::MUSIC_VOLUME);
    scene->setFocus(true);
}

void Game::update()
{
    Timer::update();
    updateFpsIndicator();
    pollEvents();
    updateSceneLogic(m_currentScene);
}

void Game::render()
{
    m_render->getWindow().clear();
    m_currentScene->display(getRender()->getWindow());
    m_render->getWindow().display();
}
