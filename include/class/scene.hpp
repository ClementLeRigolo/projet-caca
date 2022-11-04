#ifndef _SCENE_HPP
#define _SCENE_HPP

#include "libs.hpp"

class Scene
{
    private:
        int m_index;
        RectangleShape m_background;

    public:
        void update();
        void draw();
};

#endif