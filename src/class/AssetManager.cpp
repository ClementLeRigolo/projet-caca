#include "class/AssetManager.hpp"

// Loader

AssetManager::AssetManager()
{
    //fonts
    loadFont(DEBUG_FONT, DEBUG_FONT_PATH);
    loadFont(INGAME_FONT, GAME_FONT_PATH);

    // buttons
    loadTexture(B_CONTINUE, UI_PATH + "continue.png");
    loadTexture(B_LOAD_GAME,UI_PATH + "load_game.png");
    loadTexture(B_NEW_GAME, UI_PATH + "new_game.png");
    loadTexture(B_SETTINGS, UI_PATH + "settings.png");
    loadTexture(B_EXIT, UI_PATH + "exit.png");
    loadTexture(B_BACK, UI_PATH + "back.png");
    loadTexture(B_APPLY, UI_PATH + "apply.png");
    loadTexture(B_TICKBOX, UI_PATH + "tickbox.png");
    loadTexture(B_MOVE, UI_PATH + "move.png");
    loadTexture(B_SELECT, UI_PATH + "select.png");
    loadTexture(B_RESIZE, UI_PATH + "resize.png");
    loadTexture(B_ADD_EDITABLE, UI_PATH + "add_editable.png");

    // entities
    loadTexture(ENTITY_TEXTURE, "asset/texture/entity/entity.png");

    // background
    loadTexture(MM_BG1, BCKGRD_PATH + "background_no_char.jpg");
    loadTexture(MM_BG2, BCKGRD_PATH + "char.png");
    loadTexture(MM_BG3, BCKGRD_PATH + "embers.png");
    loadTexture(MM_BG4, BCKGRD_PATH + "smoke.png");
    loadTexture(MM_BG5, BCKGRD_PATH + "title.png");

    // slider
    loadTexture(SLIDER_IN, UI_PATH + "slider_in.png");
    loadTexture(SLIDER_OUT, UI_PATH + "slider_out.png");
    loadTexture(SLIDER_THINGY, UI_PATH + "slider_thingy.png");

    // walls
    loadTexture(W_BRICK, WALL_PATH + "brick.png");

    // Editor
    loadTexture(E_RESIZE_HINT, UI_PATH + "resize_hint.png");

    // sound
    loadSound(CLICK_SOUND , AUDIO_PATH  + "ui/click.ogg");
    loadSound(HOVER_SOUND , AUDIO_PATH  + "ui/hover.ogg");
}

AssetManager AssetManager::s_instance;

AssetManager& AssetManager::getInstance() { return s_instance; }

void AssetManager::loadTexture(TextureID identifier, string filename)
{
    unique_ptr<Texture> texture(new Texture());
    texture.get()->loadFromFile(filename);
    texture.get()->setSmooth(true);
    texture.get()->setRepeated(true);
    auto insert = m_textures.insert(make_pair(identifier, move(texture)));
    assert(insert.second);
}

void AssetManager::loadSound(SoundID identifier, string filename)
{
    unique_ptr<SoundBuffer> soundBuffer(new SoundBuffer());
    soundBuffer.get()->loadFromFile(filename);
    auto insert = m_sounds.insert(make_pair(identifier, move(soundBuffer)));
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

SoundBuffer& AssetManager::getSound(SoundID identifier)
{
    auto found = m_sounds.find(identifier);
    assert(found != m_sounds.end());
    return *found->second.get();
}


Font& AssetManager::getFont(FontID identifier)
{
    auto found = m_fonts.find(identifier);
    assert(found != m_fonts.end());
    return *found->second.get();
}
