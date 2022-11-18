#pragma once

#include "libs.hpp"

class Render
{
    private:
        RenderWindow m_window;
        bool m_vsyncEnabled;

    public:
        Render();
        void setVsyncEnabled(bool);
        bool isVsyncEnabled() const;
        RenderWindow& getWindow();
};
