#include "class/graphic/Render.hpp"

Render::Render()
{
    m_window.create(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), WINDOW_NAME, Style::Default);
    m_window.setFramerateLimit(500);
    setVsyncEnabled(false);
}

RenderWindow& Render::getWindow() { return m_window; }

void Render::setVsyncEnabled(bool toggle)
{
    m_window.setVerticalSyncEnabled(toggle);
    m_vsyncEnabled = toggle;
}

bool Render::isVsyncEnabled() const
{
    return m_vsyncEnabled;
}