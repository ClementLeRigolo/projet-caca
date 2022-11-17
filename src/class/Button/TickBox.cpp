#include "class/TickBox.hpp"
#include "class/Game.hpp"
#include "class/Asset.hpp"
#include "class/Logger.hpp"
#include "class/Settings.hpp"
#include "prototypes.hpp"

TickBox::TickBox(Vector2f size, Vector2f pos, Texture& texture, void (*onClick)(bool toggled))
{
    m_shape.setFillColor(Color::White);
    m_shape.setSize(size);
    m_shape.setTexture(&texture);
    m_shape.setTextureRect(IntRect(0, 0,
    texture.getSize().x / 3, texture.getSize().y));
    m_shape.setOrigin(getCenter(m_shape));
    setBaseScale(Vector2f(1, 1));
    m_shape.setPosition(pos);
    m_state = idle;
    m_toggled = false;
    m_onClick = onClick;
    m_clickSound.setBuffer(Asset::SOUND_CLICK);
    m_hoverSound.setBuffer(Asset::SOUND_HOVER);
}

void TickBox::setOnClick(void (*onClick)(bool toggle))
{
    m_onClick = onClick;
}

void TickBox::onClick(bool toggle)
{
    m_onClick(toggle);
}

void TickBox::update(Vector2i mousePos)
{
    FloatRect bound = m_shape.getGlobalBounds();
    IntRect t_rect = m_shape.getTextureRect();
    Vector2u t_size = m_shape.getTexture()->getSize();
    static bool playHoverSound = true;

    if (DoMouseIntersect(mousePos, bound)) {
        setScale(vectAdd(getBaseScale(), Vector2f(0.1, 0.1)));
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
            if (m_toggled == false)
                m_toggled = true;
            else
                m_toggled = false;
            onClick(m_toggled);
            m_state = idle;
        } else if (Mouse::isButtonPressed(Mouse::Left)) {
            m_state = pressed;
            t_rect.left = t_size.x / 1.5;
        }
        if (m_state == idle && !m_toggled) {
            m_state = hover;
            t_rect.left = t_size.x / 3;
        }
    } else {
        setScale(getBaseScale());
        if (m_state != idle && !m_toggled) {
            playHoverSound = true;
            m_state = idle;
            t_rect.left = 0;
        }
    }
    m_shape.setTextureRect(t_rect);

}
