#pragma once

#include "libs.hpp"
#include "Button.hpp"
#include "Entity.hpp"
#include "EText.hpp"

class Scene
{
    protected:
        int m_index;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_fpsText;
        vector<Button> m_buttons;

    public:
        Scene();
        int getIndex() const;
        void setIndex(int index);
        RectangleShape& getBackground();
        void setBackground(RectangleShape background);
        RectangleShape& getForeground();
        void setForeground(RectangleShape foreground);
        View& getView();
        void setView(View view);
        Text& getText();
        virtual void pollEvents(RenderWindow& window);
        virtual void updateLogic(RenderWindow& window);
        virtual void display(RenderWindow& window);
};

class MainMenu : public Scene
{
    private:
        vector<RectangleShape> m_background;

    public:
        MainMenu();
        void updateLogic(RenderWindow& window);
        void display(RenderWindow& window);
};

class SettingsMenu : public Scene
{
    private:
        vector<EText> m_text;

    public:
        SettingsMenu();
        void pollEvents(RenderWindow& window);
        void updateLogic(RenderWindow& window);
        void display(RenderWindow& window);
};

class Level : public Scene
{
    private:
        Text m_levelTitle;
        vector<Entity*> m_entities;

    public:
        Level();
        ~Level();
        void addEntity(Vector2f pos);
        void updateLogic(RenderWindow& window);
        void display(RenderWindow& window);
};