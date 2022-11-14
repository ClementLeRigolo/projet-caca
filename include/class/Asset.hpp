#pragma once

#include "libs.hpp"

class Asset
{
    public:
        static void loadAssets();

        // fonts
        static Font FONT;

        // textures
        static Texture PLAY_TEXTURE;
        static Texture EXIT_TEXTURE;
        static Texture ENTITY_TEXTURE;
};