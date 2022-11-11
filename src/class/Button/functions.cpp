#include "class/Game.hpp"
#include "class/Collection.hpp"

void doNothingFunc() {};

void exempleFunc()
{
    Level* level = (Level*)Game::getInstance().getCurrentScene();

    level->addEntity(Vector2f(randomNumber(0, 1920), randomNumber(0, 1920)));
    cout << Timer::getSeconds() << endl;
}

void buttonExitGameFunc()
{
    Game::getInstance().getRender()->getWindow()->close();
}

void buttonBackMainMenuFunc()
{
    Game::getInstance().setCurrentScene(&Collection::MAIN_MENU);
}

void buttonGoToSettingsFunc()
{
    Game::getInstance().setCurrentScene(&Collection::SETTINGS_MENU);
}

void buttonPlayGameFunc()
{
    Game::getInstance().setCurrentScene(&Collection::LEVEL_1);
}