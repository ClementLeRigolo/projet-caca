#include "class/Button.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

Button::Button()
{
    m_shape.setFillColor(Color::White);
    m_shape.setSize(Vector2f(100, 75));
    m_onClick = &exempleFunc;
}

Button::Button(Texture* texture, void (*onClick)())
{
    m_shape.setFillColor(Color::White);
    m_shape.setSize(Vector2f(100, 75));
    m_shape.setTexture(texture);
    m_shape.setTextureRect(IntRect(0, 0,
    texture->getSize().x / 3, texture->getSize().y));
    m_shape.setOrigin(getCenter(m_shape));
    m_state = idle;
    m_onClick = onClick;
}

void Button::setTexture(Texture* texture)
{
    m_shape.setTexture(texture);
    m_shape.setTextureRect(IntRect(0, 0,
    texture->getSize().x / 3, texture->getSize().y));
    m_shape.setOrigin(getCenter(m_shape));
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

RectangleShape* Button::getShape()
{
    return &m_shape;
}

void Button::update(Vector2i mousePos)
{
    FloatRect bound = m_shape.getGlobalBounds();
    IntRect t_rect = m_shape.getTextureRect();
    Vector2u t_size = m_shape.getTexture()->getSize();

    if (DoMouseIntersect(mousePos, bound)) {
        if (m_state == 2 && !Mouse::isButtonPressed(Mouse::Left)) {
            onClick();
            m_state = 0;
        } else if (Mouse::isButtonPressed(Mouse::Left)) {
            m_state = 2;
            t_rect.left = t_size.x / 1.5;
        }
        if (m_state == 0) {
            m_state = 1;
            t_rect.left = t_size.x / 3;
        }
    } else if (m_state != 0) {
        m_state = 0;
        t_rect.left = 0;
    }
    m_shape.setTextureRect(t_rect);
}
