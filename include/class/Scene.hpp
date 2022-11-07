#pragma once

#include "libs.hpp"

class Scene
{
    private:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_text;

    public:
        Scene();
        int getIndex() const;
        void setIndex(int index);
        RectangleShape* getBackground();
        void setBackground(RectangleShape background);
        RectangleShape* getForeground();
        void setForeground(RectangleShape foreground);
        View* getView();
        void setView(View view);
        Text* getText();
        virtual void display(RenderWindow* window);
};