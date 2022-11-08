#include "class/Asset.hpp"

void Asset::loadAssets()
{
    FONT.loadFromFile(FONT_PATH);
    BUTTON_TEXTURE.loadFromFile("asset/textures/play.png");
    ENTITY_TEXTURE.loadFromFile("asset/textures/entity.png");
}

//fonts
Font Asset::FONT = Font();
Texture Asset::BUTTON_TEXTURE = Texture();
Texture Asset::ENTITY_TEXTURE = Texture();