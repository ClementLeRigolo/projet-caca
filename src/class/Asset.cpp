#include "class/Asset.hpp"

void Asset::loadAssets()
{
    FONT.loadFromFile(FONT_PATH);
    TEST_TEXTURE.loadFromFile("asset/textures/test.png");
}

//fonts
Font Asset::FONT = Font();
Texture Asset::TEST_TEXTURE = Texture();