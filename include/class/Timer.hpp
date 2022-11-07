#include "libs.hpp"

class Timer
{
    private:
        Clock m_clock;
        Time m_currentTime;
        Time m_prevTime;
        float m_fps;
        float m_seconds;
        float m_frameDelta;
    public:
        Timer();
        void update();
        float getFps() const;
        float getFrameDelta() const;
        float getSeconds() const;
        ~Timer();
};

