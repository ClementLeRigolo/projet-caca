#include "class/Game.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Timer.hpp"
void updateTextInputBox(Event& event, EText& inputBox);

LevelEditor::LevelEditor()
{
    m_texturePickerBG.setSize(Vector2f(600, SCREEN_SIZE.y));
    m_texturePickerBG.setOrigin(getCenter(m_texturePickerBG));
    m_texturePickerBG.setTexture(&GET_TEXTURE(E_TEXTURE_PICKER_BG));
    m_texturePickerBG.setPosition(300, SCREEN_SIZE.y / 2.0);

    m_texturePickerFG = m_texturePickerBG;
    m_texturePickerFG.setTexture(&GET_TEXTURE(E_TEXTURE_PICKER_FG));

    m_savePopup = TextInputPopup(EText(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2), "Save Level"),
    EText(Vector2f(500, 500), "Enter save name"), &buttonCloseLevelEditorSave, &buttonApplyLevelEditorSave);
    m_savePopup.getBackground().setScale(3.5, 3.5);
    m_savePopup.getMessage().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.47);
    m_savePopup.getTitle().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.42);
    m_savePopup.getTitle().setStyle(Text::Underlined);
    m_savePopup.getInput().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.54);

    m_loadPopup = TextInputPopup(EText(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2), "Load Level"),
    EText(Vector2f(500, 500), "Enter level name"), &buttonCloseLevelEditorLoad, &buttonApplyLevelEditorLoad);
    m_loadPopup.getBackground().setScale(3.5, 3.5);
    m_loadPopup.getMessage().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.47);
    m_loadPopup.getTitle().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.42);
    m_loadPopup.getTitle().setStyle(Text::Underlined);
    m_loadPopup.getInput().setPosition(SCREEN_SIZE.x / 2, SCREEN_SIZE.y * 0.54);

    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), "Back", &buttonBackMainMenuFunc));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.65,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_MOVE), &buttonLevelEditorMoveMode, "Move"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.70,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_SELECT), &buttonLevelEditorSelectMode, "Select"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.75,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_RESIZE), &buttonLevelEditorResizeMode, "Resize"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.80,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_ADD), &buttonLevelEditorPlaceMode, "Place"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_SAVE), &buttonShowLevelEditorSave, "Save"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.90,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_LOAD), &buttonShowLevelEditorLoad, "Load"));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.95,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_COLLISION), &buttonLevelEditorCollisionMode, "Collider"));

    m_layerHint.setFont(GET_FONT(INGAME_FONT));
    m_layerHint.setOutlineColor(sf::Color::Black);
    m_layerHint.setOutlineThickness(1);
    m_layerHint.setPosition(SCREEN_SIZE.x * 0.82, SCREEN_SIZE.y * 0.95);

    reloadScene();
}

LevelEditor::~LevelEditor()
{
    for (auto& asset : m_assets)
        delete(asset);
    m_assets.clear();
}

void LevelEditor::reloadScene()
{
    m_index = 0;
    m_hasFocus = false;

    m_saving = false;
    m_mode = EditMode::MOVE;
    m_hoveringShape = false;
    m_hoveringTexturePicker = false;
    m_cameraView.setSize(SCREEN_SIZE);
    m_cameraView.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_zoomFactor = 1;
    m_selectedShape = NULL;
    m_texturePickerOffset = 0;
    m_resizableAsset = true;
    m_selectedTexture = NULL;
    m_layerHint.setString("No object selected");

    for (auto& asset : m_assets)
        delete(asset);
    m_assets.clear();

    map<String, unique_ptr<ITexture>>& map = Game::getInstance().getAssetManager().getTextureMap();

    {
        int i = 0;
        float posy = 0;
        float posx = SCREEN_SIZE.x * 0.2;
        for (auto const& [key, val] : map)
        {
            m_assetsTextures.push_back(ISprite());
            m_assetsTextures.at(i).setIdentifier(val.get()->getIdentifier());
            m_assetsTextures.at(i).setTexture(*val);
            m_assetsTextures.at(i).setOrigin(getCenter(m_assetsTextures.at(i)));
            m_assetsTextures.at(i).setScale(3, 3);
            if (i > 1) {
                posy = m_assetsTextures.at(i - 2).getGlobalBounds().height\
                + m_assetsTextures.at(i - 2).getGlobalBounds().top\
                + (m_assetsTextures.at(i).getGlobalBounds().height);
            }
            if (i % 2 == 0) {
                posx = SCREEN_SIZE.x * 0.1;
            } else if (i > 0) {
                posx = SCREEN_SIZE.x * 0.2;
            }
            m_assetsTextures.at(i).setPosition(posx, posy);
            i++;
        }
    }
}

float LevelEditor::getZoom() const { return m_zoomFactor; }

void LevelEditor::toggleSavePopup(bool toggle) { m_savePopup.setDisplayed(toggle); }

void LevelEditor::toggleLoadPopup(bool toggle) { m_loadPopup.setDisplayed(toggle); }

void LevelEditor::setSaving(bool toggle) { m_saving = toggle; }

void LevelEditor::setLoading(bool toggle) { m_loading = toggle; }

View& LevelEditor::getCamera() { return m_cameraView; }

bool LevelEditor::loadLevel(const char* path, String levelName)
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
    m_assets.clear();
    for (auto elem : entriesArray) {
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
        EditableShape* newShape;
        if (textureIdentifier.compare("NULL") != 0)
            newShape = new EditableShape(map.at(textureIdentifier).get(),
            pos, size);
        else if (hasCollision)
            newShape = new EditableHitbox(pos, size);
        newShape->setOffset(offset);
        newShape->setGrabbedSide(grabbedSide);
        newShape->setOrigin(origin);
        newShape->setGrabbed(grabbed);
        newShape->setLayer(layer);
        newShape->setBaseColor(baseColor);

        newShape->init();
        newShape->setPosition(pos);

        m_assets.push_back(newShape);
    }
    if (!parsed)
        Logger::error("Could not load file");
    return parsed;
}

void LevelEditor::saveLevel(const char *path, String levelName)
{
    Json::Value event;
    Json::Value finalEvent;
    Json::Value vec(Json::arrayValue);
    if (!filesystem::exists(path))
        filesystem::create_directory(path);
    ofstream saveFile(path + levelName + ".lvl");

    for (auto i : m_assets) {
        event["textureIdentifier"] = i->getTextureIdentifier();
        event["hasCollision"] = i->hasCollision();
        event["position"]["x"] = i->getPosition().x;
        event["position"]["y"] = i->getPosition().y;
        event["size"]["x"] = i->getSize().x;
        event["size"]["y"] = i->getSize().y;
        event["origin"]["x"] = i->getOrigin().x;
        event["origin"]["y"] = i->getOrigin().y;
        event["scale"]["x"] = i->getScale().x;
        event["scale"]["y"] = i->getScale().y;
        event["offset"]["x"] = i->getOffset().x;
        event["offset"]["y"] = i->getOffset().y;
        event["grabbedSide"]["x"] = i->getGrabbedSide().x;
        event["grabbedSide"]["y"] = i->getGrabbedSide().y;
        event["grabbed"] = i->getGrabbed();
        event["layer"] = i->getLayer();
        event["baseColor"]["r"] = i->getBaseColor().r;
        event["baseColor"]["g"] = i->getBaseColor().g;
        event["baseColor"]["b"] = i->getBaseColor().b;
        event["baseColor"]["a"] = i->getBaseColor().a;
        vec.append(event);
    }
    finalEvent["obstacles"] = vec;
    saveFile << finalEvent << std::endl;
    saveFile.close();
}

void LevelEditor::setEditMode(EditMode::ID mode) { m_mode = mode; }

void LevelEditor::addAsset(Vector2f pos)
{
    if (m_selectedTexture == NULL) {
        std::cout << "new hitbox" << std::endl;
        m_assets.push_back(new EditableHitbox(pos, sf::Vector2f(100, 100)));
    } else {
        m_assets.push_back(new EditableShape(m_selectedTexture,
        pos, Vector2f(m_selectedTexture->getSize())));
    }
}

void LevelEditor::cameraController(RenderWindow& window)
{
    static bool grabbed = 0;
    static Vector2i lastPosition = getMousePosition(window);
    Vector2i mousePos = getMousePosition(window);
    Vector2f diff = Vector2f(0, 0);

    if (Mouse::isButtonPressed(Mouse::Right) && Keyboard::isKeyPressed(Keyboard::LShift)) {
        grabbed = true;
        if (lastPosition.x != mousePos.x
            || lastPosition.y != mousePos.y) {
            diff.x = (lastPosition.x - mousePos.x) * m_zoomFactor;
            diff.y = (lastPosition.y - mousePos.y) * m_zoomFactor;
            getCamera().setCenter(vectAdd(getCamera().getCenter(), diff));
        }
    } else {
        grabbed = false;
    }
    lastPosition = getMousePosition(window);
}

void LevelEditor::pollEvents(RenderWindow& window)
{
    Event event = Game::getInstance().getEvent();

    switch (event.type) {
        case Event::Resized:
            getCamera() = getLetterboxView(getCamera(), window.getSize().x, window.getSize().y);
            break;
        case Event::TextEntered:
            m_savePopup.updateEvent(event);
            m_loadPopup.updateEvent(event);
            break;
        case Event::MouseWheelScrolled:
            if (!m_hoveringTexturePicker) {
                if (event.mouseWheelScroll.delta > 0 && m_zoomFactor > 0.15f) {
                    m_cameraView.zoom(0.9);
                    m_zoomFactor *= 0.9;
                } else if (event.mouseWheelScroll.delta < 0 && m_zoomFactor < 4.0f) {
                    m_cameraView.zoom(1.1);
                    m_zoomFactor *= 1.1;
                }
            } else {
                if (event.mouseWheelScroll.delta > 0) {
                    m_texturePickerOffset = 20;
                } else if (event.mouseWheelScroll.delta < 0) {
                    m_texturePickerOffset = -20;
                }
            }
            break;
        case Event::MouseButtonPressed:
            if (!m_hoveringTexturePicker) {
                if (event.mouseButton.button == Mouse::Left && !m_hoveringShape
                    && m_mode == EditMode::PLACE && !m_savePopup.isDisplayed()) {
                    window.setView(m_cameraView);
                    addAsset(Vector2f(getMousePosition(window)));
                    m_selectedShape = m_assets.at(m_assets.size() - 1);
                }
            }
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Add) {
                m_selectedShape->setLayer(m_selectedShape->getLayer() + 1);
            }
            if (event.key.code == Keyboard::Subtract) {
                m_selectedShape->setLayer(m_selectedShape->getLayer() - 1);
            }
            break;
    }
}

void LevelEditor::updateButtons(RenderWindow& window)
{
    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i)->update(getMousePosition(window));
        if (DoMouseIntersect(getMousePosition(window), m_buttons.at(i)->getShape().getGlobalBounds()))
            m_hoveringShape = true;
    }
}

void LevelEditor::updateEditables(RenderWindow& window)
{
    window.setView(m_cameraView);
    for (auto& asset : m_assets) {
        asset->setFillColor(asset->getBaseColor());
        asset->setResizableHintVisible(false);
    }
    for (int j = m_assets.size() - 1; j >= 0; j--) {
        for (int i = 0; i < 4; i++)
            m_assets.at(j)->getResizeHints()[i].setScale(Vector2f(getZoom(), getZoom()));
        if (DoMouseIntersect(getMousePosition(window), m_assets.at(j)->getGlobalBounds()) && m_mode == EditMode::SELECT) {
            m_assets.at(j)->setFillColor(smoothColor(Color::White, Color::Green, 0.5));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectedShape = m_assets.at(j);
                m_assets.at(j)->setFillColor(smoothColor(Color::White, Color::Blue, 0.5));
                break;
            }
            break;
        }
    }
    if (m_selectedShape != NULL) {
        m_layerHint.setString("Object is at layer " + to_string(m_selectedShape->getLayer()));
        m_selectedShape->setFillColor(smoothColor(Color::White, Color::Blue, 0.5));

        if (m_mode == EditMode::MOVE)
            m_selectedShape->dragMove(window, getZoom());

        if (m_mode == EditMode::RESIZE) {
            m_selectedShape->resizeHintReposition(m_zoomFactor);
            m_selectedShape->setResizableHintVisible(true);
            m_selectedShape->dragResize(window);
        } else
            m_selectedShape->setResizableHintVisible(false);

        if (Keyboard::isKeyPressed(Keyboard::Delete)) {
            auto it = std::find(m_assets.begin(), m_assets.end(), m_selectedShape);
            if (it != m_assets.end())
                m_assets.erase(it);
            m_selectedShape = NULL;
        }
    } else {
        m_layerHint.setString("No object selected");
    }

    std::sort(m_assets.begin(), m_assets.end(), EditableShape::comp);

    window.setView(m_view);
}

void LevelEditor::updateLogic(RenderWindow& window)
{
    m_hoveringShape = false;

    if (DoMouseIntersect(getMousePosition(window), m_texturePickerBG.getGlobalBounds())) {
        m_hoveringTexturePicker = true;
        for (auto &i : m_assetsTextures) {
            if (DoMouseIntersect(getMousePosition(window), i.getGlobalBounds())) {
                if (Mouse::isButtonPressed(Mouse::Left)) {
                    m_selectedTexture = (ITexture*)i.getTexture();
                    m_selectedTexture->setIdentifier(i.getIdentifier());
                    m_resizableAsset = false;
                }
                i.setScale(Vector2f(3.1, 3.1));
            } else
                i.setScale(Vector2f(3.0, 3.0));
            i.move(0.0f, m_texturePickerOffset);
        }
    } else {
        m_hoveringTexturePicker = false;
    }

    if (!m_savePopup.isDisplayed())
        updateButtons(window);

    if (!m_hoveringTexturePicker)
        cameraController(window);

    if (!m_hoveringShape && !m_savePopup.isDisplayed() && !m_hoveringTexturePicker)
        updateEditables(window);

    m_savePopup.update(window);
    m_loadPopup.update(window);

    if (m_saving) {
        saveLevel("levels/", m_savePopup.getInput().getString());
        m_saving = false;
    }
    if (m_loading) {
        loadLevel("levels/", m_loadPopup.getInput().getString());
        m_loading = false;
    }
    m_texturePickerOffset = 0;
}

void LevelEditor::display(RenderWindow& window)
{
    // Update player
    Player& player = Game::getInstance().getPlayer();
    window.setView(getCamera());

    // Draw world
    window.draw(m_background);

    for (auto i : m_assets)
        i->draw(window);

    player.draw(window);

    // Set view to static view and draw hud
    window.setView(m_view);
    window.draw(m_texturePickerBG);
    for (auto const& i : m_assetsTextures)
        window.draw(i);
    window.draw(m_texturePickerFG);
    for (int i = m_buttons.size() - 1; i >= 0; i--)
        m_buttons.at(i)->draw(window);
    m_savePopup.display(window);
    m_loadPopup.display(window);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
    window.draw(m_layerHint);
}