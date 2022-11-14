#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Collection.hpp"
#include "prototypes.hpp"

Level::Level()
{
    m_index = 0;

    m_backMainMenu.setTexture(&Asset::EXIT_TEXTURE);
    m_backMainMenu.getShape().setSize(Vector2f(250, 100));
    m_backMainMenu.setPos(Vector2f(SCREEN_SIZE.x * 0.1, SCREEN_SIZE.y * 0.95));
    m_backMainMenu.setOnClick(&buttonBackMainMenuFunc);

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

void Level::updateLogic(RenderWindow& window)
{
    Game::getInstance().getPlayer().update();
    m_backMainMenu.update(getMousePosition(window));
}

void Level::display(RenderWindow& window)
{
    // Update player view and draw world
    Player& player = Game::getInstance().getPlayer();
    player.viewFollow();
    window.setView(player.getView());
    window.draw(m_background);
    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i)->draw(window);
    player.draw(window);

    // Set view to static view and draw hud
    window.setView(m_view);
    window.draw(m_backMainMenu.getShape());
    window.draw(m_levelTitle);
    window.draw(m_fpsText);
}