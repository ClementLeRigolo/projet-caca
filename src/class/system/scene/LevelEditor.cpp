#include "class/Game.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Timer.hpp"
void updateTextInputBox(Event& event, EText& inputBox);

LevelEditor::LevelEditor()
{
    reloadScene();
}

void LevelEditor::reloadScene()
{
    m_index = 0;
    m_hasFocus = false;

    m_saving = false;
    m_saveGUIopen = false;
    m_mode = EditMode::MOVE;
    m_hoveringShape = false;
    m_cameraView.setSize(SCREEN_SIZE);
    m_cameraView.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_zoomFactor = 1;
    m_selectedShape = NULL;
    m_selectedShapeIndex = -1;

    m_saveGUIShape.setTexture(&GET_TEXTURE(E_SAVE_GUI), false);
    m_saveGUIShape.setSize((Vector2f)GET_TEXTURE(E_SAVE_GUI).getSize());
    m_saveGUIShape.setOrigin(getCenter(m_saveGUIShape));
    m_saveGUIShape.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    m_saveHintText = EText(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.45), "Enter save name");
    m_saveHintText.setCharacterSize(35);
    m_saveHintText.setOrigin(getCenter(m_saveHintText));
    m_saveText = EText(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.52), "");


    m_saveApllyButton.getShape().setScale(Vector2f(0.7, 0.7));
    m_saveApllyButton = Button(Vector2f(SCREEN_SIZE.x * 0.6,
    SCREEN_SIZE.y * 0.65), "Apply", &buttonApplyLevelEditorSave);

    m_saveCancelButton.getShape().setScale(Vector2f(0.7, 0.7));
    m_saveCancelButton = Button(Vector2f(SCREEN_SIZE.x * 0.4,
    SCREEN_SIZE.y * 0.65), "Cancel", &buttonHideLevelEditorSave);

    m_buttons.push_back(new Button(Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), "Back", &buttonBackMainMenuFunc));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.7,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_ADD), &buttonLevelEditorMoveMode));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.75,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_SELECT), &buttonLevelEditorSelectMode));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.80,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_RESIZE), &buttonLevelEditorResizeMode));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_ADD), &buttonLevelEditorPlaceMode));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.90,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_ADD), &buttonShowLevelEditorSave));

    m_buttons.push_back(new IconButton(Vector2f(SCREEN_SIZE.x * 0.95,
    SCREEN_SIZE.y * 0.1), &GET_TEXTURE(I_ADD), &doNothingFunc));
}

void LevelEditor::toggleSaveGUI(bool toggle)
{
    m_saveGUIopen = toggle;
}

void LevelEditor::setSaving(bool toggle)
{
    m_saving = toggle;
}

View& LevelEditor::getCamera()
{
    return m_cameraView;
}

bool LevelEditor::loadLevel(const char* path, String levelName)
{
    levelName += ".lvl";
    string content = read_file((string)path + levelName);
    Json::Reader reader;
    Json::Value root;
    Vector2f pos(0, 0);
    Vector2f size(0, 0);
    bool parsed = false;

    parsed = reader.parse(content, root, false);
    auto entriesArray = root["obstacles"];
    m_obstacles.clear();
    for (int i = 0; i < entriesArray.size(); i++) {
        auto elem = entriesArray[i];
        pos.x = elem["position"]["x"].asInt();
        pos.y = elem["position"]["y"].asInt();
        size.x = elem["size"]["x"].asInt();
        size.y = elem["size"]["y"].asInt();
        m_obstacles.push_back(EditableShape(&GET_TEXTURE(W_BRICK), pos, size));
    }
    if (!parsed)
        Logger::error("Could not parse file");
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

    for (int i = 0; i < m_obstacles.size(); i++) {
        event["position"]["x"] = m_obstacles.at(i).getPosition().x;
        event["position"]["y"] = m_obstacles.at(i).getPosition().y;
        event["size"]["x"] = m_obstacles.at(i).getSize().x;
        event["size"]["y"] = m_obstacles.at(i).getSize().y;
        vec.append(event);
    }
    finalEvent["obstacles"] = vec;
    saveFile << finalEvent << std::endl;
    saveFile.close();
}

void LevelEditor::setEditMode(EditMode::ID mode)
{
    m_mode = mode;
}

void LevelEditor::addObstacle(Vector2f pos)
{
    m_obstacles.push_back(EditableShape(&GET_TEXTURE(W_BRICK), pos, Vector2f(GET_TEXTURE(W_BRICK).getSize())));
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
        case Event::TextEntered:
            if (m_saveGUIopen) {
                updateTextInputBox(event, m_saveText);
                string s = m_saveText.getString(); 
                s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return !std::isalnum(c); }), s.end());
                m_saveText.setString(s);
                m_saveText.setOrigin(getCenter(m_saveText));
            }
            break;
        case Event::MouseWheelScrolled:
            if (event.mouseWheelScroll.delta > 0 && m_zoomFactor > 0.15f) {
                m_cameraView.zoom(0.9);
                m_zoomFactor *= 0.9;
            } else if (event.mouseWheelScroll.delta < 0 && m_zoomFactor < 4.0f) {
                m_cameraView.zoom(1.1);
                m_zoomFactor *= 1.1;
            }
            break;
        case Event::MouseButtonPressed:
            if (event.mouseButton.button == Mouse::Left && !m_hoveringShape && m_mode == EditMode::PLACE) {
                window.setView(m_cameraView);
                addObstacle(Vector2f(getMousePosition(window)));
                m_selectedShape = &m_obstacles.at(m_obstacles.size() - 1);
            }
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::L) {
                loadLevel("levels/", "preview");
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
    for (int i = 0; i < m_obstacles.size(); i++) {
        if (DoMouseIntersect(getMousePosition(window), m_obstacles.at(i).getGlobalBounds()) && m_mode == EditMode::SELECT) {
            m_obstacles.at(i).setFillColor(smoothColor(Color::White, Color::Green, 0.5));
            if (Mouse::isButtonPressed(Mouse::Left)) {
                m_selectedShape = &m_obstacles.at(i);
                m_selectedShapeIndex = i;
                m_obstacles.at(i).setFillColor(smoothColor(Color::White, Color::Blue, 0.5));
            }
        } else {
            m_obstacles.at(i).setFillColor(Color::White);
            m_obstacles.at(i).setResizableHintVisible(false);
        }
    }
    if (m_selectedShape != NULL) {
        m_selectedShape->setFillColor(smoothColor(Color::White, Color::Blue, 0.5));

        if (m_mode == EditMode::MOVE) {
            m_selectedShape->dragMove(window);
        }

        if (m_mode == EditMode::RESIZE) {
            m_selectedShape->resizeHintReposition(m_zoomFactor);
            m_selectedShape->setResizableHintVisible(true);
            m_selectedShape->dragResize(window);
        } else
            m_selectedShape->setResizableHintVisible(false);

        if (Keyboard::isKeyPressed(Keyboard::Delete)) {
            m_obstacles.erase(m_obstacles.begin() + m_selectedShapeIndex);
            m_selectedShape = NULL;
        }
    }
    window.setView(m_view);
}

void LevelEditor::updateLogic(RenderWindow& window)
{
    m_hoveringShape = false;

    if (!m_saveGUIopen)
        updateButtons(window);

    cameraController(window);

    if (!m_hoveringShape && !m_saveGUIopen)
        updateEditables(window);

    if (m_saveGUIopen) {
        m_saveApllyButton.update(getMousePosition(window));
        m_saveCancelButton.update(getMousePosition(window));
    }

    if (m_saving) {
        saveLevel("levels/", m_saveText.getString());
        m_saving = false;
    }
}

void LevelEditor::display(RenderWindow& window)
{
    // Update player
    Player& player = Game::getInstance().getPlayer();
    window.setView(getCamera());

    // Draw world
    window.draw(m_background);

    for (int i = 0; i < m_obstacles.size(); i++)
        m_obstacles.at(i).draw(window);

    player.draw(window);

    // Set view to static view and draw hud
    window.setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i)->display(window);
    if (m_saveGUIopen) {
        window.draw(m_saveGUIShape);
        window.draw(m_saveApllyButton.getShape());
        window.draw(m_saveCancelButton.getShape());
        window.draw(m_saveHintText);
        window.draw(m_saveText);
    }
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}