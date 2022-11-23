#include "class/ui/EText.hpp"
#include "class/AssetManager.hpp"

EText::EText()
{
    setFont(GET_FONT(INGAME_FONT));
    setString("Empty string");
    setPosition(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.5));
    setOutlineThickness(1);
}

EText::EText(Vector2f pos, String str)
{
    setFont(GET_FONT(INGAME_FONT));
    setString(str);
    setPosition(pos);
    setOutlineThickness(1);
}
