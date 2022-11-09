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

void buttonBackMainMenuFunc()
{
    Game::instance->getRender()->setCurrentScene(&Collection::MAIN_MENU);
}

void buttonPlayGameFunc()
{
    Game::instance->getRender()->setCurrentScene(&Collection::LEVEL_1);
}