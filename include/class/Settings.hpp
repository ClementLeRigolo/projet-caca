#pragma once

#include "libs.hpp"

class Settings
{
    public:
        static void loadSettings();

        //fonts
        static bool fullscreen;
        static float globalVolume;
        static float sfxVolume;
        static float musicVolume;
};