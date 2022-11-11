#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "prototypes.hpp"

MainMenu::MainMenu() {
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.4), Asset::B_CONTINUE_TEX, &buttonPlayGameFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.5), Asset::B_NEW_GAME_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.6), Asset::B_LOAD_GAME_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.7), Asset::B_SETG_TEX, &buttonGoToSettingsFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.8), Asset::B_EXT_TEX, &buttonExitGameFunc));
}

void MainMenu::updateLogic(RenderWindow* window)
{
    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i).update(getMousePosition(window));
    }
}

void MainMenu::display(RenderWindow* window)
{
    window->setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++) {
        window->draw(m_buttons.at(i).getShape());
    }
    window->draw(m_background);
    window->draw(m_foreground);
    window->draw(m_fpsText);
}