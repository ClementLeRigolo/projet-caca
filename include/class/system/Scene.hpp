#pragma once

#include "class/ui/TickBox.hpp"
#include "class/ui/Slider.hpp"
#include "class/ui/Popup.hpp"
#include "class/Entity.hpp"
#include "class/graphic/FadeLayer.hpp"
#include "class/world/Obstacle.hpp"
#include "class/EditableShape.hpp"
#include "enum/Editor.hpp"

class Scene
{
    protected:
        int m_index;
        bool m_hasFocus;
        RectangleShape m_background;
        RectangleShape m_foreground;
        View m_view;
        Text m_fpsText;
        vector<Button*> m_buttons;
        FadeLayer m_fadeLayer;
        Music* m_music;

    public:
        Scene();
        ~Scene();
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
        RectangleShape m_title;

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
    protected:
        Text m_levelTitle;
        vector<Entity> m_entities;
        vector<Obstacle> m_obstacles;

    public:
        Level();
        virtual void addEntity(Vector2f pos);
        virtual void updateLogic(RenderWindow& window);
        virtual void display(RenderWindow& window);
};

class LevelEditor : public Scene
{
    private:
        float m_zoomFactor;
        View m_cameraView;
        EditableShape* m_selectedShape;
        vector<EditableShape> m_obstacles;
        RectangleShape m_saveGUIShape;
        Button m_saveApllyButton;
        Button m_saveCancelButton;
        EText m_saveHintText;
        EText m_saveText;
        int m_selectedShapeIndex;
        bool m_hoveringShape;
        bool m_saving;
        unsigned int m_mode;
        bool m_saveGUIopen;

    private:
        void updateEditables(RenderWindow& window);
        void updateButtons(RenderWindow& window);
        void cameraController(RenderWindow& window);
        void saveLevel(const char *path, String saveName);

    public:
        LevelEditor();
        View& getCamera();
        void setSaving(bool toggle);
        void toggleSaveGUI(bool toggle);
        void setEditMode(EditMode::ID mode);
        void pollEvents(RenderWindow& window);
        void addEntity(Vector2f pos);
        void updateLogic(RenderWindow& window);
        void addObstacle(Vector2f pos);
        void display(RenderWindow& window);
};