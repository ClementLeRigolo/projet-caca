#pragma once

#include "libs.hpp"

class Asset
{
    private:
        static void smoothTextures();

    public:
        static void loadAssets();

        //fonts
        static Font FONT;
        static Texture _TEXTURE;
        static Texture B_CONTINUE_TEX;
        static Texture B_LOAD_GAME_TEX;
        static Texture B_NEW_GAME_TEX;
        static Texture B_BACK_TEX;
        static Texture B_APPLY_TEX;
        static Texture B_SETG_TEX;
        static Texture B_EXT_TEX;
        static Texture ENTITY_TEXTURE;
};