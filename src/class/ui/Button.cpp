#include "class/Game.hpp"
#include "class/ui/Button.hpp"
#include "class/system/Logger.hpp"
#include "class/system/Settings.hpp"
#include "prototypes.hpp"

Button::Button()
{
    m_shape.setFillColor(Color::White);
    m_shape.setSize(Vector2f(100, 75));
    m_onClick = &doNothingFunc;
    m_clickSound.setBuffer(GET_SOUND(CLICK_SOUND));
    m_hoverSound.setBuffer(GET_SOUND(HOVER_SOUND));
    m_baseScale = Vector2f(1, 1);
}

Button::Button(Vector2f pos, string label, void (*onClick)())
{
    m_shape.setFillColor(Color::White);
    m_shape.setTexture(&GET_TEXTURE(B_GENERIC));
    m_shape.setTextureRect(IntRect(0, 0,
        m_shape.getTexture()->getSize().x / 3, m_shape.getTexture()->getSize().y));
    m_shape.setSize(Vector2f(m_shape.getTextureRect().width, m_shape.getTextureRect().height));
    m_shape.setPosition(pos);
    m_shape.setOrigin(getCenter(m_shape));
    m_shape.setScale(Vector2f(3, 3));
    m_label.setString(label);
    m_label.setFillColor(Color(80, 80, 80, 255));
    m_label.setPosition(m_shape.getPosition());
    m_label.setOrigin(getCenter(m_label));
    m_state = idle;
    m_onClick = onClick;
    m_clickSound.setBuffer(GET_SOUND(CLICK_SOUND));
    m_hoverSound.setBuffer(GET_SOUND(HOVER_SOUND));
    m_baseScale = Vector2f(1, 1);
}

void Button::setTexture(Texture* texture)
{
    m_shape.setTexture(texture);
    m_shape.setTextureRect(IntRect(0, 0,
    texture->getSize().x / 3, texture->getSize().y));
    m_shape.setOrigin(getCenter(m_shape));
    m_baseScale = Vector2f(1, 1);
}

void Button::setOnClick(void (*onClick)())
{
    m_onClick = onClick;
}

void Button::onClick()
{
    m_onClick();
}

void Button::setPos(Vector2f pos)
{
    m_shape.setPosition(pos);
}

void Button::setScale(Vector2f scale)
{
    m_shape.setScale(scale);
}

void Button::setBaseScale(Vector2f scale)
{
    m_shape.setScale(scale);
    m_baseScale = scale;
}

Vector2f Button::getPosition()
{
    return m_shape.getPosition();
}

void Button::setPosition(Vector2f pos)
{
    m_shape.setPosition(pos);
}

Vector2f Button::getBaseScale()
{
    return m_baseScale;
}

Vector2f Button::getScale()
{
    return m_shape.getScale();
}

RectangleShape& Button::getShape()
{
    return m_shape;
}

void Button::update(Vector2i mousePos)
{
    FloatRect bound = m_shape.getGlobalBounds();
    IntRect t_rect = m_shape.getTextureRect();
    Vector2u t_size = m_shape.getTexture()->getSize();
    static bool playHoverSound = true;

    if (DoMouseIntersect(mousePos, bound)) {
        if (playHoverSound) {
            playHoverSound = false;
            m_hoverSound.setVolume(Settings::SFX_VOLUME);
            modulateSound(&m_hoverSound, 1.0, 1.15);
            m_hoverSound.play();
        }
        if (m_state == pressed && !Mouse::isButtonPressed(Mouse::Left)) {
            m_clickSound.setVolume(Settings::SFX_VOLUME);
            modulateSound(&m_clickSound, 0.95, 1.05);
            m_clickSound.play();
            onClick();
            m_state = idle;
        } else if (Mouse::isButtonPressed(Mouse::Left)) {
            m_state = pressed;
            t_rect.left = t_size.x / 1.5;
            m_shape.setScale(Vector2f(2.9, 2.9));
            m_label.setFillColor(Color::White);
        }
        if (m_state == idle) {
            m_state = hover;
            t_rect.left = t_size.x / 3;
            m_shape.setScale(Vector2f(3.1, 3.1));
            m_label.setFillColor(Color::White);
        }
    } else if (m_state != idle) {
        playHoverSound = true;
        m_state = idle;
        t_rect.left = 0;
        m_shape.setScale(Vector2f(3, 3));
        m_label.setFillColor(Color(80, 80, 80, 255));
    }
    m_shape.setTextureRect(t_rect);
    m_shape.setOrigin(getCenter(m_shape));
}

void Button::display(RenderTarget& target)
{
    target.draw(m_shape);
    target.draw(m_label);
}
