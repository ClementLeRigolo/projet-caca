#include "class/Timer.hpp"

static Clock m_clock;
static Time m_currentTime;
static Time m_prevTime;
static float m_fps;
static float m_seconds;
static float m_frameDelta;

void Timer::start()
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

float Timer::getFps() { return m_fps; }

float Timer::getSeconds() { return m_seconds; }

float Timer::getFrameDelta() { return m_frameDelta; }