#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "prototypes.hpp"

SettingsMenu::SettingsMenu() {
    m_buttons.push_back(Button(Vector2f(400, 200), Vector2f(SCREEN_SIZE.x / 2,
    SCREEN_SIZE.y * 0.3), Asset::B_APPLY_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(400, 200), Vector2f(SCREEN_SIZE.x / 2,
    SCREEN_SIZE.y * 0.5), Asset::B_BACK_TEX, &buttonBackMainMenuFunc));
}

void SettingsMenu::updateLogic(RenderWindow* window)
{
    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i).update(getMousePosition(window));
    }
}

void SettingsMenu::display(RenderWindow* window)
{
    window->setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++) {
        window->draw(m_buttons.at(i).getShape());
    }
    window->draw(m_background);
    window->draw(m_foreground);
    window->draw(m_fpsText);
}