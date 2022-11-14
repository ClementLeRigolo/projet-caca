#pragma once

#include "libs.hpp"

class EText : public sf::Text
{
    private:

    public:
        EText();
        EText(Vector2f pos, String str);
};