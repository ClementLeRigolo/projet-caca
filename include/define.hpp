#pragma once

#define WINDOW_NAME "Rpg masterclass"
#define SCREEN_SIZE (sf::Vector2f){1920, 1080}

#define UI_PATH (std::string)"asset/texture/ui/"
#define BCKGRD_PATH (std::string)"asset/background/"
#define DEBUG_FONT_PATH (std::string)"asset/font/debug_font.ttf"
#define GAME_FONT_PATH (std::string)"asset/font/game_font.ttf"
#define AUDIO_PATH (std::string)"asset/audio/"

#define GRAVITY 9.81;

#define GET_TEXTURE(TextureID) AssetManager::getInstance().getTexture(TextureID)
#define GET_SOUND(SoundID) AssetManager::getInstance().getSound(SoundID)
#define GET_FONT(FontID) AssetManager::getInstance().getFont(FontID)
