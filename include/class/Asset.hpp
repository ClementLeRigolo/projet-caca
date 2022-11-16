#pragma once

#include "libs.hpp"

class Asset
{
    private:
        static void smoothTextures();

    public:
        static void loadAssets();

        //fonts
        static Font INGAME_FONT;
        static Font DEBUG_FONT;
        static Texture _TEXTURE;
        static Texture B_CONTINUE_TEX;
        static Texture B_LOAD_GAME_TEX;
        static Texture B_NEW_GAME_TEX;
        static Texture B_BACK_TEX;
        static Texture B_APPLY_TEX;
        static Texture B_SETG_TEX;
        static Texture B_EXT_TEX;
        static Texture ENTITY_TEXTURE;
        static Texture MM_BG1;
        static Texture MM_BG2;
        static Texture MM_BG3;
        static Texture MM_BG4;
        static Texture MM_BG5;
        static Texture SLIDER_IN;
        static Texture SLIDER_THINGY;
        static Texture SLIDER_OUT;
};