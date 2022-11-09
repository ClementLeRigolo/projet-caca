#pragma once

#include "libs.hpp"

class Timer
{
    public:
        static void start();
        static void update();
        static float getFps();
        static float getFrameDelta();
        static float getSeconds();
};

