#ifndef _RENDER_HPP
#define _RENDER_HPP

#include "libs.hpp"
#include "class/scene.hpp"

class Render
{
    private:
        RenderWindow m_window;
        Scene m_currentScene;
        View m_view;
        bool m_fullscreen;

};

#endif