#pragma once

#include "libs.hpp"

class Button
{
    private:
        RectangleShape m_shape;
        enum ButtonStates {
            idle,
            hover,
            pressed,
        };
        unsigned short m_state;
        void (*m_onClick)();

    public:
        Button();
        Button(Texture* texture, void (*onClick)());
        void setPos(Vector2f pos);
        void setOnClick(void (*onClick)());
        void onClick();
        void setTexture(Texture* texture);
        RectangleShape* getShape();
        void update(Vector2i mousePos);
};
