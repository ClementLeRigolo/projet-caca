#pragma once

#include "libs.hpp"

class Settings
{
    public:
        static void loadSettings();

        //fonts
        static bool FULLSCREEN;
        static int FRAMERATE_LIMIT;
        static float GLOBAL_VOLUME;
        static float SFX_VOLUME;
        static float MUSIC_VOLUME;
};