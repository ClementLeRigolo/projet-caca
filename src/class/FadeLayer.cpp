#include "class/FadeLayer.hpp"
#include "class/Timer.hpp"

FadeLayer::FadeLayer()
{
    m_clockBuffer = 0;
    m_progress = 0;
    setSize(SCREEN_SIZE);
    setOrigin(vectMult(SCREEN_SIZE, 0.5));
    setPosition(vectMult(SCREEN_SIZE, 0.5));
    setScale(Vector2f(1.02, 1.02));
    setFillColor(Color::Black);
}

bool FadeLayer::isDone()
{
    if (getFillColor().a <= 0)
        return true;
    return false;
}

void FadeLayer::reset()
{
    m_progress = 0;
    setFillColor(Color::Black);
}

void FadeLayer::fade(float duration, float power)
{
    if (Timer::getSeconds() > m_clockBuffer) {
        m_progress += Timer::getSeconds() - m_clockBuffer;
        m_clockBuffer = Timer::getSeconds();
    }

    Color fadeColor = getFillColor();
    fadeColor = smoothColor(Color(0, 0, 0, 0), Color::Black,
    pow(m_progress, power) / duration);
    setFillColor(fadeColor);
}