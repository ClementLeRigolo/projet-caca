#pragma once

#include "class/ui/TickBox.hpp"
#include "class/ui/Slider.hpp"
#include "class/ui/Popup.hpp"
#include "class/Entity.hpp"
#include "class/graphic/FadeLayer.hpp"
#include "class/world/Obstacle.hpp"
#include "class/EditableShape.hpp"
#include "class/ISprite.hpp"
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
        void doTransition();
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
        virtual void reloadScene();
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
        void reloadScene();
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
        void reloadScene();
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
        void reloadScene();
        bool loadLevel(string path, string levelName);
};

class LevelEditor : public Scene
{
    private:
        float m_zoomFactor;
        View m_cameraView;
        EditableShape* m_selectedShape;
        vector<EditableShape*> m_assets;
        vector<EditableShape> m_decorations;
        vector<ISprite> m_assetsTextures;
        RectangleShape m_texturePickerBG;
        RectangleShape m_texturePickerFG;
        bool m_hoveringShape;
        bool m_saving;
        bool m_loading;
        bool m_hoveringTexturePicker;
        bool m_resizableAsset;
        ITexture* m_selectedTexture;
        float m_texturePickerOffset;
        unsigned int m_mode;
        TextInputPopup m_savePopup;
        TextInputPopup m_loadPopup;

    private:
        void updateEditables(RenderWindow& window);
        void updateButtons(RenderWindow& window);
        void cameraController(RenderWindow& window);
        void saveLevel(const char *path, String levelName);
        bool loadLevel(const char *path, String levelName);

    public:
        LevelEditor();
        View& getCamera();
        void toggleSavePopup(bool toggle);
        void toggleLoadPopup(bool toggle);
        void setSaving(bool toggle);
        void setLoading(bool toggle);
        void setEditMode(EditMode::ID mode);
        void pollEvents(RenderWindow& window);
        void addEntity(Vector2f pos);
        void updateLogic(RenderWindow& window);
        void addObstacle(Vector2f pos, bool resizable);
        void display(RenderWindow& window);
        void reloadScene();
        float getZoom() const;
};