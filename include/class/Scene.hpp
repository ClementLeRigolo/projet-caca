#pragma once

#include "libs.hpp"
#include "Button.hpp"
#include "Entity.hpp"

class Scene
{
    private:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_text;
        Button m_button;
        vector<Entity*> m_entities;

    public:
        Scene();
        void update(RenderWindow* window);
        void addEntity(Vector2f pos);
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