#pragma once

#include "libs.hpp"

class Scene
{
    private:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;

    public:
        Scene();
        int getIndex() const;
        void setIndex(int index);
        RectangleShape getBackground() const;
        void setBackground(RectangleShape background);
        RectangleShape getForeground() const;
        void setForeground(RectangleShape foreground);
        virtual void display(RenderWindow* window);
};