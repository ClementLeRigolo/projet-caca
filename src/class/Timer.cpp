#include "class/Timer.hpp"

Timer::Timer(/* args */)
{
    m_fps = 0;
    m_frameDelta = 0;
}

void Timer::update()
{
    static int i = 0;
    m_currentTime = m_clock.getElapsedTime();
    m_seconds = m_currentTime.asSeconds();

    if (i == 0) {
        m_prevTime = m_currentTime;
        i = 1;
    }
    if (m_currentTime.asSeconds() - m_prevTime.asSeconds() == 0) {
        m_fps = 0;
        return;
    }
    m_fps = 1.0f / (m_currentTime.asSeconds() - m_prevTime.asSeconds());
    m_frameDelta = (m_currentTime.asSeconds() - m_prevTime.asSeconds());
    m_prevTime = m_currentTime;
}

float Timer::getFps() const
{
    return m_fps;
}

float Timer::getSeconds() const
{
    return m_seconds;
}

float Timer::getFrameDelta() const
{
    return m_frameDelta;
}