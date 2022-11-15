#pragma once

#include "libs.hpp"

class FadeLayer : public RectangleShape
{
    public:
        float m_clockBuffer;
        float m_progress;

    public:
        FadeLayer();
        void fade(float rate, Color targetColor);
        bool isDone(Color target);
        void reset();
};