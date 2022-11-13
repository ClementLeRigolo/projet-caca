#include "class/Asset.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

SettingsMenu::SettingsMenu() {
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.7,
    SCREEN_SIZE.y * 0.9), Asset::B_APPLY_TEX, &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.3,
    SCREEN_SIZE.y * 0.9), Asset::B_BACK_TEX, &buttonBackMainMenuFunc));

    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.2, SCREEN_SIZE.y * 0.1), "Global volume"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.2, SCREEN_SIZE.y * 0.2), "SFX volume"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.2, SCREEN_SIZE.y * 0.3), "Music volume"));
}

void SettingsMenu::updateLogic(RenderWindow* window)
{
    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i).update(getMousePosition(window));
}

static void updateTextInputBox(Event& event, Text& inputBox)
{
    if (event.type == Event::TextEntered &&
        event.key.code != 8 &&
        !Keyboard::isKeyPressed(Keyboard::Enter)) {
        if (event.text.unicode < 128)
            inputBox.setString(inputBox.getString() + event.text.unicode);
    }

    if (event.type == Event::TextEntered &&
        event.key.code == 8) {
        std::string str = inputBox.getString();
        if (str.size() > 0)
            str.pop_back();
        inputBox.setString(str);
    }

    if (event.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::Enter)) {
        std::string str = inputBox.getString();
        str += "\n";
        inputBox.setString(str);
    }
}

void SettingsMenu::pollEvents(RenderWindow* window)
{
    Event event = Game::getInstance().getEvent();

    while (window->pollEvent(event)) {
        switch (event.type) {
            case Event::Closed:
                window->close();
                break;
            case Event::TextEntered:
                //updateTextInputBox(event, m_testText);
                break;
        }
    }
}

void SettingsMenu::display(RenderWindow* window)
{
    window->setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        window->draw(m_buttons.at(i).getShape());
    for (int i = 0; i < m_text.size(); i++)
        window->draw(m_text.at(i));
    window->draw(m_background);
    window->draw(m_foreground);
    window->draw(m_fpsText);
}