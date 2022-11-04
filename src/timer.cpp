#include "libs.hpp"
#include "class/timer.hpp"

Timer::Timer()
{
   update();
}

void Timer::update()
{
    static int i = 0;

    m_currentTime = m_clock.getElapsedTime();

    if (i == 0) {
        m_prevTime = m_currentTime;
        i = 1;
    }
    if ((m_currentTime.asSeconds() - m_prevTime.asSeconds() == 0))
        return;
    m_frameDelta = (m_currentTime.asSeconds() - m_prevTime.asSeconds());
    m_fps = 1.0f / (m_currentTime.asSeconds() - m_prevTime.asSeconds());
    m_prevTime = m_currentTime;
}

float Timer::getSeconds()
{
    return m_currentTime.asSeconds();
}

float Timer::getFps()
{
    return m_fps;
}

float Timer::getFrameDelta()
{
    return m_frameDelta;
}