#pragma once

#include "libs.hpp"

class ISprite : public Sprite
{
    private:
        string m_identifier;
    public:
        string getIdentifier() { return m_identifier; }
        void setIdentifier(string identifier) { m_identifier = identifier; }
};





















































