#pragma once

#include "libs.hpp"

class FadeLayer : public RectangleShape
{
    private:
        float m_clockBuffer;
        float m_progress;

    public:
        FadeLayer();
        void fade(float duration, float power);
        bool isDone();
        void reset();
};