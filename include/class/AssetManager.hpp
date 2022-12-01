#pragma once

#include "class/ITexture.hpp"
#include "enum/Assets.hpp"

class AssetManager
{
    private:
        map<TextureID, unique_ptr<Texture>> m_textures;
        map<SoundID, unique_ptr<SoundBuffer>> m_sounds;
        map<FontID, unique_ptr<Font>> m_fonts;
        map<String, unique_ptr<ITexture>> m_assetTextures;

    public:
        AssetManager();
        void loadTexture(TextureID identifier, string filename);
        Texture& getTexture(TextureID identifier);

        map<String, unique_ptr<ITexture>>& getTextureMap();

        void loadTextureFromDirectory(string directory);
        ITexture& getTexture2(String identifier);

        void loadSound(SoundID identifier, string filename);
        SoundBuffer& getSound(SoundID identifier);

        void loadFont(FontID identifier, string filename);
        Font& getFont(FontID identifier);
};
