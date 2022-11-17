#pragma once

#include "libs.hpp"
#include "TickBox.hpp"
#include "Entity.hpp"
#include "EText.hpp"
#include "Slider.hpp"
#include "class/FadeLayer.hpp"

class Scene
{
    protected:
        int m_index;
        bool m_hasFocus;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_fpsText;
        vector<Button> m_buttons;
        FadeLayer m_fadeLayer;
        Music* m_music;

    public:
        Scene();
        int getIndex() const;
        void setIndex(int index);
        void setFocus(bool boolean);
        bool hasFocus();
        RectangleShape& getBackground();
        void setBackground(RectangleShape background);
        RectangleShape& getForeground();
        void setForeground(RectangleShape foreground);
        View& getView();
        void setView(View view);
        Text& getText();
        void setMusic(Music* music);
        Music* getMusic();
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
        void pollEvents(RenderWindow& window);
        void updateLogic(RenderWindow& window);
        void display(RenderWindow& window);
};

class SettingsMenu : public Scene
{
    private:
        vector<EText> m_text;
        vector<Slider> m_sliders;
        vector<TickBox> m_tickboxs;

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
        void addEntity(Vector2f pos);
        void updateLogic(RenderWindow& window);
        void display(RenderWindow& window);
};