#include "class/graphic/Render.hpp"

Render::Render()
{
    m_window.create(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), WINDOW_NAME, Style::Default);
    m_window.setFramerateLimit(500);
    //m_window.setVerticalSyncEnabled(true);
}

RenderWindow& Render::getWindow() { return m_window; }
