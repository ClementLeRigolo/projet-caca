#include "class/Asset.hpp"

void Asset::smoothTextures()
{
    B_CONTINUE_TEX.setSmooth(true);
    B_LOAD_GAME_TEX.setSmooth(true);
    B_NEW_GAME_TEX.setSmooth(true);
    B_SETG_TEX.setSmooth(true);
    B_EXT_TEX.setSmooth(true);
    B_BACK_TEX.setSmooth(true);
    B_APPLY_TEX.setSmooth(true);
    ENTITY_TEXTURE.setSmooth(true);
}

void Asset::loadAssets()
{
    FONT.loadFromFile(FONT_PATH);
    B_CONTINUE_TEX.loadFromFile(BTON_PATH + "continue.png");
    B_LOAD_GAME_TEX.loadFromFile(BTON_PATH + "load_game.png");
    B_NEW_GAME_TEX.loadFromFile(BTON_PATH + "new_game.png");
    B_SETG_TEX.loadFromFile(BTON_PATH + "settings.png");
    B_EXT_TEX.loadFromFile(BTON_PATH + "exit.png");
    B_BACK_TEX.loadFromFile(BTON_PATH + "back.png");
    B_APPLY_TEX.loadFromFile(BTON_PATH + "apply.png");
    ENTITY_TEXTURE.loadFromFile("asset/textures/entities/entity.png");


    smoothTextures();
}

//fonts
Font Asset::FONT = Font();
Texture Asset::B_CONTINUE_TEX = Texture();
Texture Asset::B_LOAD_GAME_TEX = Texture();
Texture Asset::B_NEW_GAME_TEX = Texture();
Texture Asset::B_APPLY_TEX = Texture();
Texture Asset::B_BACK_TEX = Texture();
Texture Asset::B_SETG_TEX = Texture();
Texture Asset::B_EXT_TEX = Texture();
Texture Asset::ENTITY_TEXTURE = Texture();