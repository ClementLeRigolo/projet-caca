#include "class/system/Settings.hpp"

void Settings::loadSettings()
{
    FULLSCREEN = false;
    GLOBAL_VOLUME = 100;
    SFX_VOLUME = 50;
    MUSIC_VOLUME = 50;
    FRAMERATE_LIMIT = 500;
}

bool Settings::FULLSCREEN = false;
int Settings::FRAMERATE_LIMIT = 500;
float Settings::GLOBAL_VOLUME = 100;
float Settings::SFX_VOLUME = 50;
float Settings::MUSIC_VOLUME = 50;
