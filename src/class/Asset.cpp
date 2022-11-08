#include "class/Asset.hpp"

void Asset::loadAssets()
{
    FONT.loadFromFile(FONT_PATH);
}

//fonts
Font Asset::FONT = Font();
