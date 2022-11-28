#include "class/ui/Button.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

IconButton::IconButton() : Button() {}

IconButton::IconButton(Vector2f pos, Texture* icon, void (*onClick)())
    : Button(pos, "", onClick)
{
    m_shape.setTexture(&GET_TEXTURE(B_ICON));
    m_shape.setTextureRect(IntRect(0, 0,
        m_shape.getTexture()->getSize().x / 3, m_shape.getTexture()->getSize().y));
    m_shape.setSize(Vector2f(m_shape.getTextureRect().width, m_shape.getTextureRect().height));
    m_shape.setOrigin(getCenter(m_shape));

    if (icon != NULL)
        m_icon.setTexture(icon);
    m_icon.setSize(Vector2f(m_icon.getTexture()->getSize().x,
        m_icon.getTexture()->getSize().y));
    m_icon.setOrigin(getCenter(m_icon));
    m_icon.setPosition(m_shape.getPosition());
    m_icon.setScale(Vector2f(3, 3));
}

RectangleShape& IconButton::getIcon() { return m_icon; }

void IconButton::display(RenderTarget& target)
{
    Button::display(target);
    target.draw(m_icon);
}
