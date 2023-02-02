#include "class/Game.hpp"
#include "prototypes.hpp"
#include <memory>
#include "class/system/Logger.hpp"

Level::Level()
{
    reloadScene();
}

bool Level::loadLevel(string path, string levelName)
{
    levelName += ".lvl";
    string content = read_file((string)path + levelName);
    Json::Reader reader;
    Json::Value root;
    Vector2f pos(0, 0);
    Vector2f origin(0, 0);
    Vector2f size(0, 0);
    Vector2f scale(0, 0);
    Vector2f offset(0, 0);
    Vector2u grabbedSide(0, 0);
    int grabbed = 0;
    bool parsed = false;
    int layer = 0;
    sf::Color baseColor = sf::Color::White;
    map<String, unique_ptr<ITexture>>& map = Game::getInstance().getAssetManager().getTextureMap();

    parsed = reader.parse(content, root, false);
    auto entriesArray = root["obstacles"];
    m_platforms.clear();
    for (int i = 0; i < entriesArray.size(); i++) {
        auto elem = entriesArray[i];
        bool hasCollision = elem["hasCollision"].asBool();
        string textureIdentifier = elem["textureIdentifier"].asString();
        origin.x = elem["origin"]["x"].asFloat();
        origin.y = elem["origin"]["y"].asFloat();
        scale.x = elem["scale"]["x"].asFloat();
        scale.y = elem["scale"]["y"].asFloat();
        pos.x = elem["position"]["x"].asInt();
        pos.y = elem["position"]["y"].asInt();
        size.x = elem["size"]["x"].asInt();
        size.y = elem["size"]["y"].asInt();
        offset.x = elem["offset"]["x"].asInt();
        offset.y = elem["offset"]["y"].asInt();
        grabbedSide.x = elem["grabbedSide"]["x"].asInt();
        grabbedSide.y = elem["grabbedSide"]["y"].asInt();
        grabbed = elem["grabbed"].asInt();
        layer = elem["layer"].asInt();
        baseColor.r = elem["baseColor"]["r"].asInt();
        baseColor.g = elem["baseColor"]["g"].asInt();
        baseColor.b = elem["baseColor"]["b"].asInt();
        baseColor.a = elem["baseColor"]["a"].asInt();

        if (baseColor.a <= 0)
            baseColor = sf::Color::White;

        sf::RectangleShape* newShape = new sf::RectangleShape;

        newShape->setSize(size);
        if (textureIdentifier != "NULL")
            newShape->setTexture(map.at(textureIdentifier).get());
        else
            newShape->setFillColor(sf::Color::Transparent);
        newShape->setOrigin(origin);
        newShape->setScale(3.0, 3.0);
        newShape->setTextureRect(IntRect(offset.x / 2, newShape->getTextureRect().top, newShape->getSize().x, newShape->getSize().y));
        newShape->setPosition(pos);

        if (hasCollision) {
            m_platforms.push_back(new Collider(*newShape));
            delete(newShape);
        } else {
            m_levelDecorations.push_back(newShape);
        }

    }


    if (!parsed)
        Logger::error("Could not parse file");
    return parsed;
}

void Level::reloadScene()
{
    m_index = 0;

    m_hasFocus = false;

    m_platforms.push_back(new Collider(&GET_TEXTURE(W_BRICK), Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y), Vector2f(6000, 800)));

    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), "Exit", &buttonBackMainMenuFunc));

    m_levelTitle.setFont(GET_FONT(INGAME_FONT));
    m_levelTitle.setCharacterSize(100);
    m_levelTitle.setString("Level " + to_string(m_index));
    m_levelTitle.setOrigin(getCenter(m_levelTitle));
    m_levelTitle.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    loadLevel("levels/", "level1");

    for (int i = 0; i < 100; i++)
        addEntity(Vector2f(randomNumber(-1920, 1920 * 2), randomNumber(-500, 200 * 2)));
}

void Level::addEntity(Vector2f pos)
{
    m_entities.push_back(std::unique_ptr<Entity> (new Entity(pos)));
}

void Level::updateLogic(RenderWindow& window)
{
    CollisionInfo info;
    Player& player = Game::getInstance().getPlayer();

    player.update();

    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i)->update(getMousePosition(window));
    }

    for (int i = 0; i < m_entities.size(); i++) {
        m_entities.at(i)->update();
        for (int j = 0; j < m_platforms.size(); j++) {
            m_platforms.at(j)->checkCollision(m_entities.at(i)->getCollider(), 1.0f);
            m_entities.at(i)->getSprite().setPosition(m_entities.at(i)->getPosition());
        }
    }

    // process collision with player
    for (int i = 0; i < m_platforms.size(); i++) {
        CollisionInfo tempInfo = m_platforms.at(i)->checkCollision(player.getCollider(), 1.0f);
        if (tempInfo.getSide() != Collision::NONE)
            info = tempInfo;
    }
    // update player states
    player.updateStates(info);
    player.getSprite().setPosition(player.getPosition());
}

void Level::display(RenderWindow& window)
{
    // Update player
    Player& player = Game::getInstance().getPlayer();
    player.viewFollow();
    window.setView(player.getView());

    // Draw world
    window.draw(m_background);

    for (int i = 0; i < m_levelDecorations.size(); i++)
        window.draw((sf::RectangleShape)*m_levelDecorations.at(i));
    for (int i = 0; i < m_entities.size(); i++)
        m_entities.at(i)->draw(window);

    for (int i = 0; i < m_platforms.size(); i++)
        window.draw((sf::RectangleShape)*m_platforms.at(i));

    player.draw(window);

    // Set view to static view and draw hud
    window.setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i)->draw(window);
    window.draw(m_levelTitle);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}