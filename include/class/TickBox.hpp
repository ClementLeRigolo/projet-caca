#pragma once

#include "class/Button.hpp"

class TickBox : public Button
{
    private:
        enum ButtonStates {
            idle,
            hover,
            pressed,
        };
        bool m_toggled;
        void (*m_onClick)(bool toggled);

    public:
        TickBox();
        TickBox(Vector2f size, Vector2f pos, Texture& texture, void (*onClick)(bool toggled));
        void setOnClick(void (*onClick)(bool toggled));
        void onClick(bool toggled);
        void update(Vector2i mousePos);
};
