#include "class/Game.hpp"

void exempleFunc()
{
    Game::instance->getRender()->getCurrentScene()->addEntity(Vector2f(randomNumber(0, 960), randomNumber(0, 540)));
    cout << Timer::getSeconds() << endl;
}