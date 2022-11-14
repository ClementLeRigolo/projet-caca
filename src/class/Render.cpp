#include "class/Render.hpp"
#include "class/Collection.hpp"

Render::Render()
{
    m_window.create(VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), WINDOW_NAME, Style::Default);
    m_window.setFramerateLimit(800);
}

RenderWindow& Render::getWindow() { return m_window; }
