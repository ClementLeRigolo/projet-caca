#pragma once

#include "libs.hpp"
#include "class/ui/EText.hpp"

class Button
{
    protected:
        RectangleShape m_shape;
        EText m_label;
        enum ButtonStates {
            idle,
            hover,
            pressed,
        };
        Sound m_clickSound;
        Sound m_hoverSound;
        unsigned short m_state;
        void (*m_onClick)();
        Vector2f m_baseScale;

    public:
        Button();
        Button(Vector2f pos, string label, void (*onClick)());
        void setPos(Vector2f pos);
        void setScale(Vector2f scale);
        void setBaseScale(Vector2f scale);
        void setPosition(Vector2f pos);
        Vector2f getPosition();
        Vector2f getBaseScale();
        Vector2f getScale();
        virtual void setOnClick(void (*onClick)());
        virtual void onClick();
        void setTexture(Texture* texture);
        RectangleShape& getShape();
        virtual void update(Vector2i mousePos);
        virtual void display(RenderTarget& target);
};

class IconButton : public Button
{
    private:
        RectangleShape m_icon;

    public:
        IconButton();
        IconButton(Vector2f pos, Texture* icon, void (*onClick)());
        RectangleShape& getIcon();
        void display(RenderTarget& target) override;
};
