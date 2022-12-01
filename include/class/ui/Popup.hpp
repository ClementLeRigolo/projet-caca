#pragma once

#include "class/ui/EText.hpp"
#include "class/ui/Button.hpp"

class Popup
{
    protected:
        bool m_display;
        RectangleShape m_background;
        EText m_title;
        EText m_message;
        Button m_buttonClose;

    public:
        Popup();
        Popup(EText title, EText message, void (*onClick)());
        void setDisplayed(bool display);
        bool isDisplayed() const;
        EText& getTitle();
        EText& getMessage();
        RectangleShape& getBackground();
        virtual void update(RenderWindow& target);
        virtual void display(RenderTarget& target);
};

class TextInputPopup : public Popup
{
    private:
        EText m_input;
        Button m_buttonApply;
    public:
        TextInputPopup();
        TextInputPopup(EText title, EText message, void (*onClick1)(), void (*onClick2)());
        EText& getInput();
        void updateEvent(Event& event);
        void update(RenderWindow& target);
        void display(RenderTarget& target);
};