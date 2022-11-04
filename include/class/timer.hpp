#ifndef _TIMER_HPP
#define _TIMER_HPP

#include "libs.hpp"

class Timer
{
    private:
        Clock m_clock;
        Time m_currentTime;
        Time m_prevTime;
        float m_frameDelta;
        float m_elapsedTime;
        float m_seconds;
};

#endif