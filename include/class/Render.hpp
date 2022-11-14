#pragma once

#include "class/Scene.hpp"

class Render
{
    private:
        RenderWindow m_window;

    public:
        Render();
        RenderWindow& getWindow();
};
