#include "class/ui/Popup.hpp"
#include "class/Game.hpp"

Popup::Popup() {}

Popup::Popup(EText title, EText message, void (*onClick)())
{
    m_background.setTexture(&GET_TEXTURE(E_SAVE_GUI), false);
    m_background.setSize((Vector2f)GET_TEXTURE(E_SAVE_GUI).getSize());
    m_background.setOrigin(getCenter(m_background));
    m_background.setPosition(Vector2f(SCREEN_SIZE.x / 2, SCREEN_SIZE.y / 2));

    m_title = title;
    m_message = message;

    m_button.getShape().setScale(Vector2f(0.7, 0.7));
    m_button = Button(Vector2f(250, 100), Vector2f(SCREEN_SIZE.x * 0.6,
    SCREEN_SIZE.y * 0.65), "Close", onClick);
}

void Popup::setDisplayed(bool display) { m_display = display; }

bool Popup::isDisplayed() const { return m_display; }

void Popup::update(RenderWindow& target)
{
    if (m_display) {
        m_button.update(getMousePosition(target));
    }   
}

void Popup::display(RenderTarget& target)
{
    if (m_display)
    {
        target.draw(m_background);
        target.draw(m_title);
        target.draw(m_message);
        m_button.display(target);
    }
}
