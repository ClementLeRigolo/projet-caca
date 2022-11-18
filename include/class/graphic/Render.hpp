#pragma once

#include "libs.hpp"

class Render
{
    private:
        RenderWindow m_window;

    public:
        Render();
        RenderWindow& getWindow();
};
