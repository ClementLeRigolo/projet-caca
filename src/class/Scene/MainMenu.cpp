#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "class/Game.hpp"
#include "class/Logger.hpp"
#include "class/AssetManager.hpp"
#include "prototypes.hpp"

MainMenu::MainMenu() {
    AssetManager::loadTexture(TextureID::B_CONTINUE_TEX, BTON_PATH + "continue.png");
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.4), AssetManager::getTexture(TextureID::B_CONTINUE_TEX), &buttonPlayGameFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.5), Asset::B_NEW_GAME_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.6), Asset::B_LOAD_GAME_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.7), Asset::B_SETG_TEX, &buttonGoToSettingsFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.8), Asset::B_EXT_TEX, &buttonExitGameFunc));

    for (int i = 0; i < 5; i++) {
        m_background.push_back(RectangleShape());
        m_background.at(i).setSize(SCREEN_SIZE);
        m_background.at(i).setOrigin(getCenter(m_background.at(i)));
        m_background.at(i).setPosition(vectMult(SCREEN_SIZE, 0.5));
        m_background.at(i).setScale(Vector2f(1.02, 1.02));
    }

    m_background.at(0).setTexture(&Asset::MM_BG1);
    m_background.at(1).setTexture(&Asset::MM_BG2);
    m_background.at(2).setTexture(&Asset::MM_BG3);
    m_background.at(3).setTexture(&Asset::MM_BG4);
    m_background.at(4).setTexture(&Asset::MM_BG5);
}

void MainMenu::pollEvents(RenderWindow& window)
{
    Event &event = Game::getInstance().getEvent();
    Vector2i m_pos = getMousePosition(Game::getInstance().getRender()->getWindow());
    static Vector2i last_pos = getMousePosition(Game::getInstance().getRender()->getWindow());
    static Vector2f offset = Vector2f(0, 0);

    switch (event.type) {
        case Event::MouseMoved:
            Vector2f pos = vectMult(SCREEN_SIZE, 0.5);
            offset.x += (last_pos.x - m_pos.x) * Timer::getFrameDelta() * 20;
            offset.x = clamp(-30, 30, offset.x);
            m_background.at(1).setPosition(vectAdd(pos, vectMult(offset, -0.4)));
            m_background.at(2).setPosition(vectAdd(pos, vectMult(offset, -0.8)));
            m_background.at(3).setPosition(vectAdd(pos, vectMult(offset, 0.6)));
            last_pos = m_pos;
            break;
    }
}

void MainMenu::updateLogic(RenderWindow& window)
{
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i).update(getMousePosition(window));


    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
}

void MainMenu::display(RenderWindow& window)
{
    window.setView(m_view);
    for (int i = 0; i < m_background.size() - 1; i++)
        window.draw(m_background.at(i));
    for (int i = 0; i < m_buttons.size(); i++)
        window.draw(m_buttons.at(i).getShape());
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}