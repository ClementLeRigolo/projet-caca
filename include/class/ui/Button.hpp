#pragma once

#include "libs.hpp"

class Button
{
    protected:
        RectangleShape m_shape;
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
        Button(Vector2f size, Vector2f pos, Texture& texture, void (*onClick)());
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
};