#include "class/render.hpp"

Render::Render()
{
    VideoMode mode;
    mode.height = 600;
    mode.width = 800;
    mode.bitsPerPixel = 32;
    window.create(mode, WINDOW_NAME, Style::Default);
    window.setFramerateLimit(60);
}

Scene Render::getCurrentScene() { return m_currentScene; }

void Render::setCurrentScene(Scene scene) { m_currentScene = scene; }

View Render::getView() { return m_view; }

void Render::setView(View view) { m_view = view; }

bool Render::isFullscreen() { return m_fullscreen; }

void Render::setFullscreen(bool fullscreen) { m_fullscreen = fullscreen; }
