#include "class/Game.hpp"
#include "class/Collection.hpp"

void exempleFunc()
{
    Level* level = (Level*)Game::instance->getCurrentScene();

    level->addEntity(Vector2f(randomNumber(0, 1920), randomNumber(0, 1920)));
    cout << Timer::getSeconds() << endl;
}

void buttonExitGameFunc()
{
    Game::instance->getRender()->getWindow()->close();
}

void buttonBackMainMenuFunc()
{
    Game::instance->setCurrentScene(&Collection::MAIN_MENU);
}

void buttonPlayGameFunc()
{
    Game::instance->setCurrentScene(&Collection::LEVEL_1);
}