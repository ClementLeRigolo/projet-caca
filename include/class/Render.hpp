#pragma once

#include "libs.hpp"

class Render
{
    public:
        Render();
        virtual ~Render();
        RenderWindow* window;
        void update();
};
