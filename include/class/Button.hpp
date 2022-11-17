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
        Sound m_clickSound;
        Sound m_hoverSound;
        unsigned short m_state;
        void (*m_onClick)();

    public:
        Button();
        Button(Vector2f size, Vector2f pos, Texture& texture, void (*onClick)());
        void setPos(Vector2f pos);
        void setOnClick(void (*onClick)());
        void onClick();
        void setTexture(Texture* texture);
        RectangleShape& getShape();
        void update(Vector2i mousePos);
};
