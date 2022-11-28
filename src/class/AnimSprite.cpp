#include "class/AnimSprite.hpp"
#include "class/system/Timer.hpp"

AnimSprite::AnimSprite()
{
    setColor(Color::White);
    m_rows = 0;
    m_cols = 0;
    m_currentFrameX = 0;
    m_currentFrameY = 0;
    m_frameCount = 0;
    m_clockBuffer = 0;
    m_loop = true;
}

void AnimSprite::init(Texture &texture, int rows, int cols, bool loop)
{
    setTexture(texture, true);
    setOrigin(getCenter(texture));
    sf::IntRect rect = getTextureRect();
    sf::Vector2u t_size = getTexture()->getSize();

    m_loop = loop;
    m_rows = rows;
    m_cols = cols;
    m_frameCount = rows * cols;
    m_currentFrameX = 0;
    m_currentFrameY = 0;
    rect.left = 0;
    rect.top = 0;
    rect.width = t_size.x / cols;
    rect.height = t_size.y / rows;
    setTextureRect(rect);
    setOrigin(getCenter(*this));
}

void AnimSprite::update()
{
    IntRect rect = getTextureRect();

    if (Timer::getSeconds() > m_clockBuffer + 0.1) {
        m_clockBuffer = Timer::getSeconds();
        if (m_currentFrameX + 1 < m_cols) {
            m_currentFrameX++;
        } else if (m_currentFrameY + 1 < m_rows) {
            m_currentFrameY++;
            m_currentFrameX = 0;
        } else {
            m_currentFrameX = 0;
            m_currentFrameY = 0;
        }
        setTextureRect(IntRect(m_currentFrameX * rect.width,
        m_currentFrameY * rect.height, rect.width, rect.height));
    }
}