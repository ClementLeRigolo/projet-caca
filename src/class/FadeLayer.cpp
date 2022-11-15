#include "class/FadeLayer.hpp"
#include "class/Timer.hpp"
#include "class/Logger.hpp"

FadeLayer::FadeLayer()
{
    setSize(SCREEN_SIZE);
    setOrigin(vectMult(SCREEN_SIZE, 0.5));
    setPosition(vectMult(SCREEN_SIZE, 0.5));
    setScale(Vector2f(1.02, 1.02));
    setFillColor(Color::Black);
}

bool FadeLayer::isDone(Color target)
{
    Color color = getFillColor();
    if (color.a == target.a && color.b == target.b
        && color.r == target.r && color.g == target.g)
        return true;
    return false;
}

void FadeLayer::reset()
{
    setFillColor(Color::Black);
}

void FadeLayer::fade(float rate, Color targetColor)
{
    Color color = getFillColor();

    rate *= Timer::getFrameDelta() * 100;

    color.r = (targetColor.r - color.r) * rate + color.r;
    color.g = (targetColor.g - color.g) * rate + color.g;
    color.b = (targetColor.b - color.b) * rate + color.b;
    color.a = (targetColor.a - color.a) * rate + color.a;

    setFillColor(color);
}