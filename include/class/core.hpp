#ifndef _CORE_HPP
#define _CORE_HPP

#include "libs.hpp"
#include "class/render.hpp"
#include "class/timer.hpp"
#include "class/assets.hpp"

class Core
{
    private:
        Render* m_render;
        Timer m_timer;
        Event m_event;
        Assets m_assets;

    public:
        Core();
        Render* getRender();
        Timer getTimer();
        Event getEvent();
        Assets getAssets();
};

#endif