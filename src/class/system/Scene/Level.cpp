#include "class/Game.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"
#include "class/system/Logger.hpp"

Level::Level()
{
    m_index = 0;

    m_hasFocus = false;

    m_obstacles.push_back(Obstacle(&GET_TEXTURE(W_BRICK), Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y), Vector2f(6000, 800)));

    m_buttons.push_back(Button(Vector2f(250, 100), Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), GET_TEXTURE(B_EXIT), &buttonBackMainMenuFunc));

    m_levelTitle.setFont(GET_FONT(INGAME_FONT));
    m_levelTitle.setCharacterSize(100);
    m_levelTitle.setString("Level " + to_string(m_index));
    m_levelTitle.setOrigin(getCenter(m_levelTitle));
    m_levelTitle.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    for (int i = 0; i < 100; i++)
        addEntity(Vector2f(randomNumber(-1920, 1920 * 2), randomNumber(-1080, 1080 * 2)));
}

void Level::addEntity(Vector2f pos)
{
    m_entities.push_back(Entity(pos));
}

void Level::updateLogic(RenderWindow& window)
{
    Player& player = Game::getInstance().getPlayer();

    player.update();

    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i).update(getMousePosition(window));
    }

    for (int i = 0; i < m_entities.size(); i++) {
        m_entities.at(i).update();
        for (int j = 0; j < m_obstacles.size(); j++) {
            m_obstacles.at(j).getCollider().checkCollision(m_entities.at(i).getCollider(), 1.0f);
            m_entities.at(i).getSprite().setPosition(m_entities.at(i).getPosition());
        }
    }

    for (int i = 0; i < m_obstacles.size(); i++) {
        m_obstacles.at(i).getCollider().checkCollision(player.getCollider(), 1.0f);
        player.getSprite().setPosition(player.getPosition());
    }

    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
}

void Level::display(RenderWindow& window)
{
    // Update player
    Player& player = Game::getInstance().getPlayer();
    player.viewFollow();
    window.setView(player.getView());

    // Draw world
    window.draw(m_background);

    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i).draw(window);

    for (int i = 0; i < m_obstacles.size(); i++)
        window.draw(m_obstacles.at(i).getShape());

    player.draw(window);

    // Set view to static view and draw hud
    window.setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        window.draw(m_buttons.at(i).getShape());
    window.draw(m_levelTitle);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}