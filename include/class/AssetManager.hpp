#pragma once

#include "libs.hpp"
#include "enum/Assets.hpp"

class AssetManager
{
    public:
        static void loadTexture(TextureID identifier, string filename);
        static Texture& getTexture(TextureID identifier);
        static void loadFont(FontID identifier, string filename);
        static Font& getFont(FontID identifier);

    private:
        static map<TextureID, unique_ptr<Texture>> m_textures;
        static map<FontID, unique_ptr<Font>> m_fonts;
};