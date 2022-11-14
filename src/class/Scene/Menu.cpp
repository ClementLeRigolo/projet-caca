#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "prototypes.hpp"

Menu::Menu() {
    m_buttonPlay.setTexture(&Asset::PLAY_TEXTURE);
    m_buttonPlay.getShape().setSize(Vector2f(400, 200));
    m_buttonPlay.setPos(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.4));
    m_buttonPlay.setOnClick(&buttonPlayGameFunc);

    m_buttonExit.setTexture(&Asset::EXIT_TEXTURE);
    m_buttonExit.getShape().setSize(Vector2f(400, 200));
    m_buttonExit.setPos(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.6));
    m_buttonExit.setOnClick(&buttonExitGameFunc);
}

void Menu::updateLogic(RenderWindow& window)
{
    m_buttonPlay.update(getMousePosition(window));
    m_buttonExit.update(getMousePosition(window));
}

void Menu::display(RenderWindow& window)
{
    //for (int i = 0; i < m_entities.size(); i++)
    //    m_entities.at(i)->draw(*window);
    window.setView(m_view);
    window.draw(m_buttonPlay.getShape());
    window.draw(m_buttonExit.getShape());
    window.draw(m_background);
    window.draw(m_foreground);
    window.draw(m_fpsText);
}