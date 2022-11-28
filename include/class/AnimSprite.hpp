#pragma once

#include "libs.hpp"

class AnimSprite : public Sprite
{
    private:
        int m_rows;
        int m_cols;
        int m_frameCount;
        int m_currentFrameX;
        int m_currentFrameY;
        float m_clockBuffer;
        bool m_loop;

    public:
        AnimSprite();
        void init(Texture &texture, int rows, int cols, bool loop);
        void update();
};