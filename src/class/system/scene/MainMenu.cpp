#include "class/Game.hpp"
#include "class/system/Scene.hpp"
#include "class/system/Timer.hpp"
#include "class/system/Logger.hpp"
#include "prototypes.hpp"

MainMenu::MainMenu() {
    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.4), "Continue", &buttonPlayGameFunc));
    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.5), "New Game", &buttonGoToLevelEditor));
    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.6), "Credits", &doNothingFunc));
    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.7), "Settings", &buttonGoToSettingsFunc));
    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.8), "Quit", &buttonExitGameFunc));

    m_background.setTexture(&GET_TEXTURE(MM_BG));
    m_background.setTextureRect(IntRect(0, 0,
        m_background.getTexture()->getSize().x / 8, m_background.getTexture()->getSize().y));
    m_background.setSize(Vector2f(m_background.getTextureRect().width, m_background.getTextureRect().height));
    m_background.setOrigin(getCenter(m_background));
    m_background.setPosition(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.5));
    m_background.setScale(Vector2f(3.1, 3.1));

    m_title.setTexture(&GET_TEXTURE(TITLE_TEXTURE));
    m_title.setSize(Vector2f(m_title.getTextureRect().width, m_title.getTextureRect().height));
    m_title.setOrigin(getCenter(m_title));
    m_title.setPosition(Vector2f(SCREEN_SIZE.x * 0.5, 80));
    m_title.setScale(Vector2f(3.5, 3.5));
}

void MainMenu::pollEvents(RenderWindow& window)
{
    Event &event = Game::getInstance().getEvent();
    Vector2i m_pos = getMousePosition(Game::getInstance().getRender()->getWindow());
    static Vector2i last_pos = getMousePosition(Game::getInstance().getRender()->getWindow());
    static Vector2f offset = Vector2f(0, 0);
}

void MainMenu::updateLogic(RenderWindow& window)
{
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i)->update(getMousePosition(window));

    static float timer = Timer::getSeconds();
    IntRect rect = m_background.getTextureRect();
    if (timer + 0.13 <= Timer::getSeconds()) {
        rect.left += m_background.getTexture()->getSize().x / 8;
        m_background.setTextureRect(rect);
        timer = Timer::getSeconds();
    }

    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
}

void MainMenu::display(RenderWindow& window)
{
    window.setView(m_view);
    window.draw(m_background);
    window.draw(m_title);
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i)->display(window);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}
