#include "class/core.hpp"

Core::Core()
{
    m_render = new Render();
}

Render* Core::getRender() { return m_render; }

Timer Core::getTimer() { return m_timer; }

Event Core::getEvent() { return m_event; }

Assets Core::getAssets() { return m_assets; }