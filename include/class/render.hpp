#ifndef _RENDER_HPP
#define _RENDER_HPP

#include "libs.hpp"
#include "class/scene.hpp"

class Render
{
    private:
        Scene m_currentScene;
        View m_view;
        bool m_fullscreen;
        
    public:
        Render();
        RenderWindow window;
        Scene getCurrentScene();
        void setCurrentScene(Scene scene);
        View getView();
        void setView(View view);
        bool isFullscreen();
        void setFullscreen(bool fullscreen);
};

#endif