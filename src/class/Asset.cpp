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
    MM_BG1.setSmooth(true);
    MM_BG2.setSmooth(true);
    MM_BG3.setSmooth(true);
    MM_BG4.setSmooth(true);
    MM_BG5.setSmooth(true);
}

void Asset::loadAssets()
{
    // fonts
    DEBUG_FONT.loadFromFile(DEBUG_FONT_PATH);
    INGAME_FONT.loadFromFile(GAME_FONT_PATH);

    // textures
    // buttons
    B_CONTINUE_TEX.loadFromFile(BTON_PATH + "continue.png");
    B_LOAD_GAME_TEX.loadFromFile(BTON_PATH + "load_game.png");
    B_NEW_GAME_TEX.loadFromFile(BTON_PATH + "new_game.png");
    B_SETG_TEX.loadFromFile(BTON_PATH + "settings.png");
    B_EXT_TEX.loadFromFile(BTON_PATH + "exit.png");
    B_BACK_TEX.loadFromFile(BTON_PATH + "back.png");
    B_APPLY_TEX.loadFromFile(BTON_PATH + "apply.png");

    // entities
    ENTITY_TEXTURE.loadFromFile("asset/texture/entity/entity.png");

    // background
    MM_BG1.loadFromFile(BCKGRD_PATH + "background_no_char.jpg");
    MM_BG2.loadFromFile(BCKGRD_PATH + "char.png");
    MM_BG3.loadFromFile(BCKGRD_PATH + "embers.png");
    MM_BG4.loadFromFile(BCKGRD_PATH + "smoke.png");
    MM_BG5.loadFromFile(BCKGRD_PATH + "title.png");

    // sounds

    smoothTextures();
}

//fonts
Font Asset::INGAME_FONT = Font();
Font Asset::DEBUG_FONT = Font();
Texture Asset::B_CONTINUE_TEX = Texture();
Texture Asset::B_LOAD_GAME_TEX = Texture();
Texture Asset::B_NEW_GAME_TEX = Texture();
Texture Asset::B_APPLY_TEX = Texture();
Texture Asset::B_BACK_TEX = Texture();
Texture Asset::B_SETG_TEX = Texture();
Texture Asset::B_EXT_TEX = Texture();
Texture Asset::ENTITY_TEXTURE = Texture();
Texture Asset::MM_BG1 = Texture();
Texture Asset::MM_BG2 = Texture();
Texture Asset::MM_BG3 = Texture();
Texture Asset::MM_BG4 = Texture();
Texture Asset::MM_BG5 = Texture();
