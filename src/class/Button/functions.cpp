#include "class/Game.hpp"
#include "class/Collection.hpp"

void exempleFunc()
{
    cout << Timer::getSeconds() << endl;
}

void buttonExitGameFunc()
{
    Game::instance->getRender()->getWindow()->close();
}

void buttonPlayGameFunc()
{
    Game::instance->getRender()->setCurrentScene(&Collection::LEVEL_1);
}