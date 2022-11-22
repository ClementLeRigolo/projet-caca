#include "class/Game.hpp"
#include "class/AssetManager.hpp"
#include "prototypes.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Timer.hpp"

LevelEditor::LevelEditor()
{
    m_index = 0;
    m_hasFocus = false;

    m_mode = EditMode::MOVE;
    m_hoveringShape = false;
    m_cameraView.setSize(SCREEN_SIZE);
    m_cameraView.setCenter(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));
    m_zoomFactor = 1;
    m_selectedShape = NULL;
    m_selectedShapeIndex = -1;

    m_buttons.push_back(Button(Vector2f(250, 100), Vector2f(SCREEN_SIZE.x * 0.1,
    SCREEN_SIZE.y * 0.95), GET_TEXTURE(B_EXIT), &buttonBackMainMenuFunc));


    m_buttons.push_back(Button(Vector2f(64, 64), Vector2f(SCREEN_SIZE.x * 0.8,
    SCREEN_SIZE.y * 0.1), GET_TEXTURE(B_MOVE), &buttonLevelEditorMoveMode));

    m_buttons.push_back(Button(Vector2f(64, 64), Vector2f(SCREEN_SIZE.x * 0.85,
    SCREEN_SIZE.y * 0.1), GET_TEXTURE(B_SELECT), &buttonLevelEditorSelectMode));

    m_buttons.push_back(Button(Vector2f(64, 64), Vector2f(SCREEN_SIZE.x * 0.9,
    SCREEN_SIZE.y * 0.1), GET_TEXTURE(B_RESIZE), &buttonLevelEditorResizeMode));

    m_buttons.push_back(Button(Vector2f(64, 64), Vector2f(SCREEN_SIZE.x * 0.95,
    SCREEN_SIZE.y * 0.1), GET_TEXTURE(B_ADD_EDITABLE), &buttonLevelEditorPlaceMode));
}

View& LevelEditor::getCamera()
{
    return m_cameraView;
}

void LevelEditor::saveLevel(const char *path, String saveName)
{
    if (!std::filesystem::exists(path))
        std::filesystem::create_directory(path);
    ofstream saveFile(path + saveName + ".save");

    for (int i = 0; i < m_obstacles.size(); i++) {
        saveFile << "#obstacle {" << endl;
        saveFile << ("   position = (" + to_string((int)m_obstacles.at(i).getPosition().x) +\
        ", " + to_string((int)m_obstacles.at(i).getPosition().y) + ")") << endl;
        saveFile << ("   size = (" + to_string((int)m_obstacles.at(i).getSize().x) + ", " +\
        to_string((int)m_obstacles.at(i).getSize().y) + ")") << endl;
        saveFile << "}" << endl;
    }

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
            if (event.key.code == Keyboard::K)
                saveLevel("saves/", "new_save");
            break;
    }
}

void LevelEditor::updateLogic(RenderWindow& window)
{
    m_hoveringShape = false;
    for (int i = 0; i < m_buttons.size(); i++) {
        m_buttons.at(i).update(getMousePosition(window));
        if (DoMouseIntersect(getMousePosition(window), m_buttons.at(i).getShape().getGlobalBounds()))
            m_hoveringShape = true;
    }

    cameraController(window);
    window.setView(m_cameraView);

    if (!m_hoveringShape) {
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
    }

    // Scene transition
    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
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
        window.draw(m_buttons.at(i).getShape());
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}