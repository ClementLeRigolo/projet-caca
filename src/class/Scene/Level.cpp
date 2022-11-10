#include "class/Scene.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "class/Timer.hpp"
#include "prototypes.hpp"

Level::Level()
{
    m_index = 0;

    m_backMainMenu.setTexture(&Asset::EXIT_TEXTURE);
    m_backMainMenu.getShape()->setSize(Vector2f(250, 100));
    m_backMainMenu.setPos(Vector2f(SCREEN_SIZE.x * 0.1, SCREEN_SIZE.y * 0.95));
    m_backMainMenu.setOnClick(&buttonBackMainMenuFunc);

    m_levelTitle.setFont(Asset::FONT);
    m_levelTitle.setCharacterSize(100);
    m_levelTitle.setString("Level " + to_string(m_index));
    m_levelTitle.setOrigin(getCenter(m_levelTitle));
    m_levelTitle.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
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
    m_backMainMenu.update(getMousePosition(window));
}

void Level::display(RenderWindow* window)
{
    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i)->draw(*window);
    window->setView(m_view);
    Player::instance->draw(*window);
    window->draw(*m_backMainMenu.getShape());
    window->draw(m_levelTitle);
    window->draw(m_background);
    window->draw(m_foreground);
    window->draw(m_fpsText);
}