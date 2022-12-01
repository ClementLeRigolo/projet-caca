#pragma once

#include "libs.hpp"

class Slider
{
    private:
        Vector2i m_lastMousePos;
        Vector2f m_thingyBaseScale;
        RectangleShape m_outShape;
        RectangleShape m_inShape;
        RectangleShape m_sliderThingy;
        float m_progress;
        bool m_grabbed;

    public:
        Slider();
        Slider(Texture* outTexture, Texture* inTexture,
        Texture* sliderThingyTexture, Vector2f size,
        Vector2f pos, bool vertical);
        RectangleShape& getOutShape();
        RectangleShape& getInShape();
        RectangleShape& getSliderThingy();
        float getProgress() const;
        void setProgress(float progress);
        void setPosition(Vector2f pos);
        void setScale(Vector2f scale);
        void setSize(Vector2f size);
        bool isGrabbed();
        void limit(float limit, bool keepValue);
        void update(RenderWindow& window);
        void draw(sf::RenderTarget &target);
};
