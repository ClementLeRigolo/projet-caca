#include "class/ui/Popup.hpp"
#include "class/Game.hpp"
void updateTextInputBox(Event& event, EText& inputBox);

TextInputPopup::TextInputPopup() {}

TextInputPopup::TextInputPopup(EText title, EText message, void (*onClick1)(), void (*onClick2)())
{
    m_background.setTexture(&GET_TEXTURE(E_SAVE_GUI), false);
    m_background.setSize((Vector2f)GET_TEXTURE(E_SAVE_GUI).getSize());
    m_background.setOrigin(getCenter(m_background));
    m_background.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    m_title = title;
    m_message = message;
    m_display = false;
    m_input.setString("");

    m_buttonClose.getShape().setScale(Vector2f(0.7, 0.7));
    m_buttonClose = Button(Vector2f(SCREEN_SIZE.x * 0.4,
    SCREEN_SIZE.y * 0.7), "Close", onClick1);

    m_buttonApply.getShape().setScale(Vector2f(0.7, 0.7));
    m_buttonApply = Button(Vector2f(SCREEN_SIZE.x * 0.6,
    SCREEN_SIZE.y * 0.7), "Apply", onClick2);
}

EText& TextInputPopup::getInput() { return m_input; }

void TextInputPopup::update(RenderWindow& target)
{
    if (!isDisplayed())
        return;
    m_buttonClose.update(getMousePosition(target));
    m_buttonApply.update(getMousePosition(target));
}

void TextInputPopup::updateEvent(Event& event)
{
    if (!isDisplayed() || (m_input.getGlobalBounds().left < getBackground().getGlobalBounds().left * 1.1
        && event.key.code != 8))
        return;
    updateTextInputBox(event, m_input);
    string s = m_input.getString(); 
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return !std::isalnum(c); }), s.end());
    m_input.setString(s);
    m_input.setOrigin(getCenter(m_input));
}

void TextInputPopup::display(RenderTarget& target)
{
    if (m_display) {
        target.draw(m_background);
        target.draw(m_title);
        target.draw(m_message);
        target.draw(m_input);
        m_buttonClose.display(target);
        m_buttonApply.display(target);
    }
}
