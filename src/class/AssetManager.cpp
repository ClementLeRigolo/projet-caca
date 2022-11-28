#include "class/Game.hpp"

// Loader

AssetManager::AssetManager()
{
    //fonts
    loadFont(DEBUG_FONT, DEBUG_FONT_PATH);
    loadFont(INGAME_FONT, GAME_FONT_PATH);

    // buttons
    loadTexture(B_GENERIC, UI_PATH + "button_generic.png");
    loadTexture(B_ICON, UI_PATH + "button_icon.png");
    loadTexture(B_TICKBOX, UI_PATH + "tickbox.png");

    // icons
    loadTexture(I_ADD, UI_PATH + "icon_add.png");
    loadTexture(I_RESIZE, UI_PATH + "icon_resize.png");
    loadTexture(I_SELECT, UI_PATH + "icon_select.png");

    // entities
    loadTexture(ENTITY_TEXTURE, "asset/texture/entity/entity.png");

    // titles
    loadTexture(TITLE_TEXTURE, UI_PATH + "rpg_masterclass.png");

    // background
    loadTexture(MM_BG, BCKGRD_PATH + "main_menu_background.png");

    // slider
    loadTexture(SLIDER_IN, UI_PATH + "slider_in.png");
    loadTexture(SLIDER_OUT, UI_PATH + "slider_out.png");
    loadTexture(SLIDER_THINGY, UI_PATH + "slider_thingy.png");

    // walls
    loadTexture(W_BRICK, WALL_PATH + "brick.png");

    // Editor
    loadTexture(E_RESIZE_HINT, UI_PATH + "resize_hint.png");
    loadTexture(E_SAVE_GUI, UI_PATH + "saveGUI.png");
    loadTexture(B_SAVE, UI_PATH + "save.png");
    loadTexture(B_MOVE, UI_PATH + "move.png");
    loadTexture(B_SELECT, UI_PATH + "select.png");
    loadTexture(B_RESIZE, UI_PATH + "resize.png");
    loadTexture(B_LOAD, UI_PATH + "load.png");
    loadTexture(B_ADD_EDITABLE, UI_PATH + "add_editable.png");

    // Player
    loadTexture(P_IDLE, PLAYER_PATH + "idle.png");
    loadTexture(P_RUN, PLAYER_PATH + "run.png");
    loadTexture(P_JUMP, PLAYER_PATH + "jump.png");
    loadTexture(P_FALL, PLAYER_PATH + "fall.png");
    loadTexture(P_HANG, PLAYER_PATH + "hang.png");

    // sound
    loadSound(CLICK_SOUND , AUDIO_PATH  + "ui/click.ogg");
    loadSound(HOVER_SOUND , AUDIO_PATH  + "ui/hover.ogg");
}

void AssetManager::loadTexture(TextureID identifier, string filename)
{
    unique_ptr<Texture> texture(new Texture());
    texture.get()->loadFromFile(filename);
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
