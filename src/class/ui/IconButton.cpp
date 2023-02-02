#include "class/ui/Button.hpp"
#include "class/Game.hpp"
#include "prototypes.hpp"

IconButton::IconButton(Vector2f pos, Texture* icon, void (*onClick)(), std::string hoverHintString)
: Button(pos, "", onClick)
{
    m_shape.setTexture(&GET_TEXTURE(B_ICON));
    m_shape.setTextureRect(IntRect(0, 0,
    m_shape.getTexture()->getSize().x / 3, m_shape.getTexture()->getSize().y));
    m_shape.setSize(Vector2f(m_shape.getTextureRect().width, m_shape.getTextureRect().height));
    m_shape.setOrigin(Vector2f(m_shape.getTextureRect().width / 2, m_shape.getTextureRect().height / 2));

    m_hoverHint.setFont(GET_FONT(INGAME_FONT));
    m_hoverHint.setOutlineColor(sf::Color::Black);
    m_hoverHint.setOutlineThickness(1);
    m_hoverHint.setString(hoverHintString);
    m_hoverHint.setOrigin(0, m_hoverHint.getGlobalBounds().height);

    if (icon != NULL)
        m_icon.setTexture(icon);
    m_icon.setSize(Vector2f(m_icon.getTexture()->getSize().x,
        m_icon.getTexture()->getSize().y));
    m_icon.setOrigin(getCenter(m_icon));
    m_icon.setPosition(m_shape.getPosition());
    m_icon.setScale(Vector2f(3, 3));
}

RectangleShape& IconButton::getIcon() { return m_icon; }

void IconButton::draw(RenderTarget& target)
{
    Button::draw(target);
    target.draw(m_icon);
    if (m_state == hover) {
        m_hoverHint.setPosition(sf::Vector2f(getMousePosition(target)));
        target.draw(m_hoverHint);
    }
}
