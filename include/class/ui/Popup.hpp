#pragma once

#include "class/ui/EText.hpp"
#include "class/ui/Button.hpp"

class Popup
{
    private:
        bool m_display;
        RectangleShape m_background;
        EText m_title;
        EText m_message;
        Button m_button;

    public:
        Popup();
        Popup(EText title, EText message, void (*onClick)());
        void setDisplayed(bool display);
        bool isDisplayed() const;
        virtual void update(RenderWindow& target);
        virtual void display(RenderTarget& target);
};