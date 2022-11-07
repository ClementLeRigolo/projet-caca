#pragma once

#include "libs.hpp"

class Scene
{
    private:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;
        Text m_text;

    public:
        Scene();
        int getIndex() const;
        void setIndex(int index);
        Text* getText();
        RectangleShape* getBackground();
        void setBackground(RectangleShape background);
        RectangleShape* getForeground();
        void setForeground(RectangleShape foreground);
        virtual void display(RenderWindow* window);
};