#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "prototypes.hpp"

Level::Level()
{
    m_index = 0;

    m_buttons.push_back(Button(Vector2f(250, 100), Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), Asset::B_EXT_TEX, &buttonBackMainMenuFunc));

    m_levelTitle.setFont(Asset::FONT);
    m_levelTitle.setCharacterSize(100);
    m_levelTitle.setString("Level " + to_string(m_index));
    m_levelTitle.setOrigin(getCenter(m_levelTitle));
    m_levelTitle.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    for (int i = 0; i < 100; i++)
        addEntity(Vector2f(randomNumber(-1920, 1920 * 2), randomNumber(-1080, 1080 * 2)));
}

void Level::addEntity(Vector2f pos)
{
    m_entities.push_back(new Entity(pos));
}

Level::~Level()
{
    for (int i = 0; i < m_entities.size(); i++)
        delete m_entities.at(i);
}

void Level::updateLogic(RenderWindow* window)
{
    Player::instance->update();
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i).update(getMousePosition(window));
}

void Level::display(RenderWindow* window)
{
    // Update player view and draw world
    Player::instance->viewFollow();
    window->setView(*Player::instance->getView());
    window->draw(m_background);
    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i)->draw(*window);
    Player::instance->draw(*window);

    // Set view to static view and draw hud
    window->setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        window->draw(m_buttons.at(i).getShape());
    window->draw(m_levelTitle);
    window->draw(m_fpsText);
}