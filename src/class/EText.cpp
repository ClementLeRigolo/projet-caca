#include "class/EText.hpp"
#include "class/Asset.hpp"

EText::EText()
{
    setFont(Asset::INGAME_FONT);
    setString("Empty string");
    setPosition(Vector2f(SCREEN_SIZE.x * 0.5, SCREEN_SIZE.y * 0.5));
}

EText::EText(Vector2f pos, String str)
{
    setFont(Asset::INGAME_FONT);
    setString(str);
    setPosition(pos);
}
