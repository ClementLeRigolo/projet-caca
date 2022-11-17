#pragma once

#include "libs.hpp"
#include "enum/Assets.hpp"

class AssetManager
{
    private:
        static AssetManager s_instance;
        AssetManager();
        map<TextureID, unique_ptr<Texture>> m_textures;
        map<SoundID, unique_ptr<SoundBuffer>> m_sounds;
        map<FontID, unique_ptr<Font>> m_fonts;

    public:
        static AssetManager& getInstance();
        void loadTexture(TextureID identifier, string filename);
        Texture& getTexture(TextureID identifier);

        void loadSound(SoundID identifier, string filename);
        SoundBuffer& getSound(SoundID identifier);

        void loadFont(FontID identifier, string filename);
        Font& getFont(FontID identifier);

};