#include "class/AssetManager.hpp"

map<TextureID, unique_ptr<Texture>> AssetManager::m_textures = map<TextureID, unique_ptr<Texture>>();
map<FontID, unique_ptr<Font>> AssetManager::m_fonts = map<FontID, unique_ptr<Font>>();

// Loader

void AssetManager::loadTexture(TextureID identifier, string filename)
{
    unique_ptr<Texture> texture(new Texture());
    texture.get()->loadFromFile(filename);
    auto insert = m_textures.insert(make_pair(identifier, move(texture)));
    assert(insert.second);
}

void AssetManager::loadFont(FontID identifier, string filename)
{
    unique_ptr<Font> font(new Font());
    font.get()->loadFromFile(filename);
    auto insert = m_fonts.insert(make_pair(identifier, move(font)));
    assert(insert.second);
}

// Getter

Texture& AssetManager::getTexture(TextureID identifier)
{
    auto found = m_textures.find(identifier);
    assert(found != m_textures.end());
    return *found->second.get();
}

Font& AssetManager::getFont(FontID identifier)
{
    auto found = m_fonts.find(identifier);
    assert(found != m_fonts.end());
    return *found->second.get();
}
