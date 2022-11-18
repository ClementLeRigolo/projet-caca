#include "class/AssetManager.hpp"
#include "class/Game.hpp"
#include "class/system/Settings.hpp"
#include "prototypes.hpp"

SettingsMenu::SettingsMenu() {
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.7,
    SCREEN_SIZE.y * 0.9), GET_TEXTURE(B_APPLY_TEX), &doNothingFunc));
    m_buttons.push_back(Button(Vector2f(300, 100), Vector2f(SCREEN_SIZE.x * 0.3,
    SCREEN_SIZE.y * 0.9), GET_TEXTURE(B_BACK_TEX), &buttonBackMainMenuFunc));

    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.06), "{ Audio }"));
    m_text.at(0).setCharacterSize(50);
    m_text.at(0).setOrigin(getCenter(m_text.at(0)));

    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.45), "{ Display }"));
    m_text.at(1).setCharacterSize(50);
    m_text.at(1).setOrigin(getCenter(m_text.at(0)));

    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.3, SCREEN_SIZE.y * 0.15), "Global volume"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.3, SCREEN_SIZE.y * 0.25), "SFX volume"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.3, SCREEN_SIZE.y * 0.35), "Music volume"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.3, SCREEN_SIZE.y * 0.55), "Framerate limit"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.73, SCREEN_SIZE.y * 0.55), "[500]"));
    m_text.push_back(EText(Vector2f(SCREEN_SIZE.x * 0.3, SCREEN_SIZE.y * 0.65), "Toggle Vsync"));

    m_sliders.push_back(Slider(&GET_TEXTURE(SLIDER_OUT),
    &GET_TEXTURE(SLIDER_IN),
    &GET_TEXTURE(SLIDER_THINGY),
    Vector2f(400, 50), Vector2f(SCREEN_SIZE.x * 0.6, SCREEN_SIZE.y * 0.17)));
    m_sliders.at(0).getSliderThingy().setPosition(Vector2f((m_sliders.at(0).getInShape().getGlobalBounds().left\
    + m_sliders.at(0).getInShape().getGlobalBounds().width),
    m_sliders.at(0).getSliderThingy().getPosition().y));
    m_sliders.at(0).setProgress(1);

    m_sliders.push_back(Slider(&GET_TEXTURE(SLIDER_OUT),
    &GET_TEXTURE(SLIDER_IN),
    &GET_TEXTURE(SLIDER_THINGY),
    Vector2f(400, 50), Vector2f(SCREEN_SIZE.x * 0.6, SCREEN_SIZE.y * 0.27)));

    m_sliders.push_back(Slider(&GET_TEXTURE(SLIDER_OUT),
    &GET_TEXTURE(SLIDER_IN),
    &GET_TEXTURE(SLIDER_THINGY),
    Vector2f(400, 50), Vector2f(SCREEN_SIZE.x * 0.6, SCREEN_SIZE.y * 0.37)));

    m_sliders.push_back(Slider(&GET_TEXTURE(SLIDER_OUT),
    &GET_TEXTURE(SLIDER_IN),
    &GET_TEXTURE(SLIDER_THINGY),
    Vector2f(400, 50), Vector2f(SCREEN_SIZE.x * 0.6, SCREEN_SIZE.y * 0.57)));


    m_tickboxs.push_back(TickBox(Vector2f(50, 50), Vector2f(SCREEN_SIZE.x * 0.6,
    SCREEN_SIZE.y * 0.665), GET_TEXTURE(B_TICKBOX), &toggleVsyncFunc));
    m_tickboxs.at(0).setBaseScale(Vector2f(0.8, 0.8));
}

void SettingsMenu::updateLogic(RenderWindow& window)
{
    static int lastFrameRateLimit = Settings::FRAMERATE_LIMIT;

    for (int i = 0; i < m_buttons.size(); i++)
        m_buttons.at(i).update(getMousePosition(window));

    for (int i = 0; i < m_tickboxs.size(); i++)
        m_tickboxs.at(i).update(getMousePosition(window));

    for (int i = 0; i < m_sliders.size(); i++)
        m_sliders.at(i).update(window);

    Settings::GLOBAL_VOLUME = m_sliders.at(0).getProgress() * 100.0;
    Settings::SFX_VOLUME = (m_sliders.at(1).getProgress() * 100.0) * m_sliders.at(0).getProgress();
    Settings::MUSIC_VOLUME = (m_sliders.at(2).getProgress() * 100.0) * m_sliders.at(0).getProgress();
    Settings::FRAMERATE_LIMIT = (m_sliders.at(3).getProgress() * 1000) + 10;

    if (Settings::FRAMERATE_LIMIT == 0 || Settings::FRAMERATE_LIMIT >= 1000) {
        Settings::FRAMERATE_LIMIT = 0;
        m_text.at(6).setString("[" + (string)"unlimited" + "]");
    } else
        m_text.at(6).setString("[" + to_string(Settings::FRAMERATE_LIMIT) + "]");

    if (lastFrameRateLimit != Settings::FRAMERATE_LIMIT) {
        Game::getInstance().getRender()->getWindow().setFramerateLimit(Settings::FRAMERATE_LIMIT);
        lastFrameRateLimit = Settings::FRAMERATE_LIMIT;
    }


    if (!hasFocus()) {
        m_fadeLayer.reset();
    } else
        m_fadeLayer.fade(0.02, Color::Transparent);
}

// Unused, keeping for later
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

void SettingsMenu::pollEvents(RenderWindow& window)
{
    Event event = Game::getInstance().getEvent();

    switch (event.type) {
        case Event::TextEntered:
            //updateTextInputBox(event, m_testText);
            break;
    }
}

void SettingsMenu::display(RenderWindow& window)
{
    window.setView(m_view);
    for (int i = 0; i < m_buttons.size(); i++)
        window.draw(m_buttons.at(i).getShape());
    for (int i = 0; i < m_tickboxs.size(); i++)
        window.draw(m_tickboxs.at(i).getShape());
    for (int i = 0; i < m_text.size(); i++)
        window.draw(m_text.at(i));
    for (int i = 0; i < m_sliders.size(); i++)
        m_sliders.at(i).draw(window);
    window.draw(m_background);
    window.draw(m_foreground);
    window.draw(m_fadeLayer);
    window.draw(m_fpsText);
}