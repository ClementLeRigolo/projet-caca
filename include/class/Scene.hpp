#pragma once

#include "libs.hpp"
#include "Button.hpp"
#include "Entity.hpp"

class Scene
{
    protected:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_fpsText;

    public:
        Scene();
        virtual ~Scene();
        virtual void updateLogic(RenderWindow* window);
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

class Menu : public Scene
{
    private:
        Button m_buttonPlay;
        Button m_buttonExit;

    public:
        Menu();
        void updateLogic(RenderWindow* window);
        void display(RenderWindow* window);
};

class Level : public Scene
{
    private:
        Button m_backMainMenu;
        Text m_levelTitle;
        vector<Entity*> m_entities;

    public:
        Level();
        ~Level();
        void addEntity(Vector2f pos);
        void updateLogic(RenderWindow* window);
        void display(RenderWindow* window);
};