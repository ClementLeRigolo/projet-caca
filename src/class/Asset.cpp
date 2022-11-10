#include "class/Asset.hpp"

void Asset::loadAssets()
{
    FONT.loadFromFile(FONT_PATH);
    PLAY_TEXTURE.loadFromFile(PLAY_PATH);
    EXIT_TEXTURE.loadFromFile(EXIT_PATH);
    ENTITY_TEXTURE.loadFromFile("asset/textures/entities/entity.png");
}

//fonts
Font Asset::FONT = Font();
Texture Asset::PLAY_TEXTURE = Texture();
Texture Asset::EXIT_TEXTURE = Texture();
Texture Asset::ENTITY_TEXTURE = Texture();